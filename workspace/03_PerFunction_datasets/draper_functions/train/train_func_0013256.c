ntb_file_read(struct ntb_file *cf,
                     struct ntb_buffer *p)
{


        int c_length;
        int n_bytes_decrypted;
        unsigned char c[FILE_BUFFER_SIZE];

        if(!EVP_DecryptInit_ex(cf->env->ctx, CIPHER, NULL,
                               cf->env->key_buf.data, get_iv(cf)))
            goto decrypt_error;

        if(!seek_behind_iv(cf)) goto decrypt_error;

        while((c_length = fread(c, sizeof(char), FILE_BUFFER_SIZE, cf->file)) != 0)
        {
                int max_new_size = p->length + c_length + CIPHER_BLOCK_SIZE;
                ntb_buffer_ensure_size(p, max_new_size);

                if(!EVP_DecryptUpdate(cf->env->ctx,
                                 p->data + p->length,
                                 &n_bytes_decrypted,
                                 c, c_length)) {
                    goto decrypt_error;
                }
                p->length += n_bytes_decrypted;
        }
        if(!EVP_DecryptFinal_ex(cf->env->ctx,
                                p->data + p->length,
                                &n_bytes_decrypted))
                goto decrypt_error;

        p->length += n_bytes_decrypted;

        EVP_CIPHER_CTX_cleanup(cf->env->ctx);

        return true;

decrypt_error:
        EVP_CIPHER_CTX_cleanup(cf->env->ctx);
        return false;
}

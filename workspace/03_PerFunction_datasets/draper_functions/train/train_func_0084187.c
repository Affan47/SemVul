sec_PKCS7DecryptLength (sec_PKCS7CipherObject *obj, unsigned int input_len,
			PRBool final)
{
    int blocks, block_size;

    PORT_Assert (! obj->encrypt);

    block_size = obj->block_size;


    if (block_size == 0)
	return input_len;


    if (final)
	return obj->pending_count + input_len;


    blocks = (obj->pending_count + input_len - 1) / block_size;
    return blocks * block_size;
}

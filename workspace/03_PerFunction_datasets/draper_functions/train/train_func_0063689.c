null_cipher_alloc(cipher_t **c, int key_len) {
  extern cipher_type_t null_cipher;
  uint8_t *pointer;

  debug_print(mod_cipher,
	      "allocating cipher with key length %d", key_len);


  pointer = (uint8_t*)crypto_alloc(sizeof(null_cipher_ctx_t) + sizeof(cipher_t));
  if (pointer == NULL)
    return err_status_alloc_fail;


  *c = (cipher_t *)pointer;
  (*c)->type = &null_cipher;
  (*c)->state = pointer + sizeof(cipher_t);


  (*c)->key_len = key_len;


  null_cipher.ref_count++;

  return err_status_ok;

}

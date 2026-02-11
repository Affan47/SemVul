_calculate_k_rakp_hmac_md5 (const void *sik_key,
                            unsigned int sik_key_len,
                            void *k,
                            unsigned int k_len,
                            const void *constant,
                            unsigned int constant_len)
{
  if (!sik_key
      || !sik_key_len
      || !k
      || !k_len
      || !constant
      || !constant_len
      || (constant_len < IPMI_KEY_CONSTANT_LENGTH))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  return (_calculate_k_rakp_hmac (IPMI_CRYPT_HASH_MD5,
                                  IPMI_HMAC_MD5_DIGEST_LENGTH,
                                  sik_key,
                                  sik_key_len,
                                  k,
                                  k_len,
                                  constant,
                                  constant_len));
}

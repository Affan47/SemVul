zc_crk_ptext_set_text(struct zc_crk_ptext *ptext,
                                    const uint8_t *plaintext,
                                    const uint8_t *ciphertext,
                                    size_t size)
{
    if (size < 13)
        return -EINVAL;

    ptext->plaintext = plaintext;
    ptext->ciphertext = ciphertext;
    ptext->size = size;

    return 0;
}

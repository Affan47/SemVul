kmgcry_keybuilder(gcry_md_hd_t md_hand,
                    int digest, const size_t mdlen,
                    const unsigned char *salt,
                    const unsigned char *pass, const size_t passlen,
                    unsigned char *ckey, const size_t ckeysz,
                    unsigned char *civ, const size_t civsz)

{   size_t kpos, ivpos, pos;
    unsigned char *buff;

    kpos = ivpos = 0;
    do {

        gcry_md_reset(md_hand);

        gcry_md_write(md_hand, (const void*)salt, (size_t)kmgcry_saltlen);
        gcry_md_write(md_hand, (const void*)pass, passlen);
        if (kpos > 0) {
            gcry_md_write(md_hand, (const void*)ckey, kpos); }
        if (ivpos > 0) {
            gcry_md_write(md_hand, (const void*)civ, ivpos); }
        buff = gcry_md_read(md_hand, digest);


        pos = 0;
        while (kpos < ckeysz && pos < mdlen) {
            ckey[kpos++] = buff[pos++]; }
        while (ivpos < civsz && pos < mdlen) {
            civ[ivpos++] = buff[pos++]; }
    } while (kpos < ckeysz || ivpos < civsz);
}

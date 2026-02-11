read_key_file(const char* keyfile, R_RSA_PRIVATE_KEY& key) {
    int retval;
#ifndef _USING_FCGI_
    FILE* fkey = fopen(keyfile, "r");
#else
    FCGI_FILE* fkey = FCGI::fopen(keyfile, "r");
#endif
    if (!fkey) {
        fprintf(stderr, "can't open key file (%s)\n", keyfile);
        return ERR_FOPEN;
    }
    retval = scan_key_hex(fkey, (KEY*)&key, sizeof(key));
    fclose(fkey);
    if (retval) {
        fprintf(stderr, "can't parse key\n");
        return retval;
    }
    return 0;
}

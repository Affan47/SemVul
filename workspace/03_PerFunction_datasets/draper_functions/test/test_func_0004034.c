af_is_encrypted_segment(const char *segname){
    if(strcmp(segname,AF_AFFKEY)==0) return 1;
    if(aff::ends_with(segname,AF_AES256_SUFFIX)) return 1;
    if(strncmp(segname,AF_AFFKEY_EVP,strlen(AF_AFFKEY_EVP)-1)==0) return 1;
    return 0;
}

af_use_aes_passphrase(AFFILE *af,const char *passphrase)
{
    af_invalidate_vni_cache(af);
    if(passphrase==0 && !(af->openflags & O_RDWR)){
	af->crypto->sealing_key_set = 0;
	return 0;
    }

    if(af->crypto->sealing_key_set) return AF_ERROR_KEY_SET;

    unsigned char affkey[32];
    int r = af_get_aes_key_from_passphrase(af,passphrase,affkey);
    if(r) return r;
    r = af_set_aes_key(af,affkey,256);
    memset(affkey,0,sizeof(affkey));
    return r;
}

id3v2AddLameVersion(lame_global_flags * gfp)
{
    char    buffer[1024];
    const char *b = get_lame_os_bitness();
    const char *v = get_lame_version();
    const char *u = get_lame_url();
    const size_t lenb = strlen(b);

    if (lenb > 0) {
        sprintf(buffer, "LAME %s version %s (%s)", b, v, u);
    }
    else {
        sprintf(buffer, "LAME version %s (%s)", v, u);
    }
    copyV1ToV2(gfp, ID_ENCODER, buffer);
}

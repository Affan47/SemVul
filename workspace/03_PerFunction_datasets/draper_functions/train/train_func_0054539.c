rdt_parse_b64buf (unsigned int *target_len, const char *p)
{
    unsigned char *target;
    int len = strlen(p);
    if (*p == '\"') {
        p++;
        len -= 2;
    }
    *target_len = len * 3 / 4;
    target = av_mallocz(*target_len + FF_INPUT_BUFFER_PADDING_SIZE);
    av_base64_decode(target, p, *target_len);
    return target;
}

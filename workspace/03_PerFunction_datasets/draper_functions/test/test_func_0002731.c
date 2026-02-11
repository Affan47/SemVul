codec_get_id(const AVCodecTag *tags, unsigned int tag)
{
    int i;
    for(i=0; tags[i].id != CODEC_ID_NONE;i++) {
        if(tag == tags[i].tag)
            return tags[i].id;
    }
    for(i=0; tags[i].id != CODEC_ID_NONE; i++) {
        if(   toupper((tag >> 0)&0xFF) == toupper((tags[i].tag >> 0)&0xFF)
           && toupper((tag >> 8)&0xFF) == toupper((tags[i].tag >> 8)&0xFF)
           && toupper((tag >>16)&0xFF) == toupper((tags[i].tag >>16)&0xFF)
           && toupper((tag >>24)&0xFF) == toupper((tags[i].tag >>24)&0xFF))
            return tags[i].id;
    }
    return CODEC_ID_NONE;
}

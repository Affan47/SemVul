get_string_tag(const char* tag) const {


    uint8_t* pTag = bam_aux_get(_bp, tag);
    if (!pTag) return NULL;


    if (pTag[0] != 'Z') return NULL;
    ++pTag;

    return (const char*)pTag;
}

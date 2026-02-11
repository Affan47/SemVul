jconv_ident(ScmConvInfo *info, const char **iptr,
                          size_t *iroom, char **optr, size_t *oroom)
{
    size_t inroom = *iroom, outroom = *oroom;
#ifdef JCONV_DEBUG
    fprintf(stderr, "jconv_ident %s->%s\n", info->fromCode, info->toCode);
#endif
    if (inroom <= outroom) {
        memcpy(*optr, *iptr, inroom);
        *optr += inroom;
        *iptr += inroom;
        *iroom = 0;
        *oroom -= inroom;
        return inroom;
    } else {
        memcpy(*optr, *iptr, outroom);
        *optr += outroom;
        *iptr += outroom;
        *iroom -= outroom;
        *oroom = 0;
        return OUTPUT_NOT_ENOUGH;
    }
}

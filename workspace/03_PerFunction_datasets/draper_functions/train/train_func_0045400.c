ncx_len_NC_string(const NC_string *ncstrp)
{
        size_t sz = X_SIZEOF_SIZE_T;

        assert(ncstrp != NULL);

        if(ncstrp->nchars != 0)
        {
#if 0
                assert(ncstrp->nchars % X_ALIGN == 0);
                sz += ncstrp->nchars;
#else
                sz += _RNDUP(ncstrp->nchars, X_ALIGN);
#endif
        }
        return sz;
}

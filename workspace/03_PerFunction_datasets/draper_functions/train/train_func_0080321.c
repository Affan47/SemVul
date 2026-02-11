lame_copy_inbuffer(lame_internal_flags* gfc,
                   void const* l, void const* r, int nsamples,
                   enum PCMSampleType pcm_type, int jump, FLOAT s)
{
    SessionConfig_t const *const cfg = &gfc->cfg;
    EncStateVar_t *const esv = &gfc->sv_enc;
    sample_t* ib0 = esv->in_buffer_0;
    sample_t* ib1 = esv->in_buffer_1;
    FLOAT   m[2][2];


    m[0][0] = s * cfg->pcm_transform[0][0];
    m[0][1] = s * cfg->pcm_transform[0][1];
    m[1][0] = s * cfg->pcm_transform[1][0];
    m[1][1] = s * cfg->pcm_transform[1][1];


#define COPY_AND_TRANSFORM(T) \
{ \
    T const *bl = l, *br = r; \
    int     i; \
    for (i = 0; i < nsamples; i++) { \
        sample_t const xl = *bl; \
        sample_t const xr = *br; \
        sample_t const u = xl * m[0][0] + xr * m[0][1]; \
        sample_t const v = xl * m[1][0] + xr * m[1][1]; \
        ib0[i] = u; \
        ib1[i] = v; \
        bl += jump; \
        br += jump; \
    } \
}
    switch ( pcm_type ) {
    case pcm_short_type:
        COPY_AND_TRANSFORM(short int);
        break;
    case pcm_int_type:
        COPY_AND_TRANSFORM(int);
        break;
    case pcm_long_type:
        COPY_AND_TRANSFORM(long int);
        break;
    case pcm_float_type:
        COPY_AND_TRANSFORM(float);
        break;
    case pcm_double_type:
        COPY_AND_TRANSFORM(double);
        break;
    }
}

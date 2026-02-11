ajBtreeReadParamsS(const AjPStr file, const AjPStr ext,
                          const AjPStr idir,
                          AjBool *secondary, AjBool *compressed,
                          ajuint *kwlimit, ajuint *idlimit,
                          ajuint *refcount,
                          ajuint *pripagesize, ajuint *secpagesize,
                          ajuint *pricachesize, ajuint *seccachesize,
                          ajulong *pripagecount, ajulong *secpagecount,
                          ajuint *order, ajuint *nperbucket, ajuint *level,
                          ajuint *sorder, ajuint *snperbucket,
                          ajulong *count, ajulong *countall)
{
    return ajBtreeReadParamsC(MAJSTRGETPTR(file), MAJSTRGETPTR(ext),
                              MAJSTRGETPTR(idir), secondary, compressed,
                              kwlimit, idlimit, refcount,
                              pripagesize, secpagesize,
                              pricachesize, seccachesize,
                              pripagecount, secpagecount,
                              order, nperbucket, level,
                              sorder, snperbucket,
                              count, countall);
}

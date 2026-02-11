init_flags(ndbuf_t *ndbuf)
{
    if (ndbuf->base.ndim == 0)
        ndbuf->flags |= ND_SCALAR;
    if (ndbuf->base.suboffsets)
        ndbuf->flags |= ND_PIL;
    if (PyBuffer_IsContiguous(&ndbuf->base, 'C'))
        ndbuf->flags |= ND_C;
    if (PyBuffer_IsContiguous(&ndbuf->base, 'F'))
        ndbuf->flags |= ND_FORTRAN;
}

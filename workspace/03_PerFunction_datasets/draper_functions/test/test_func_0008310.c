ADIOI_Uses_generic_read(ADIO_File fd)
{
    ADIOI_Fns *fns = fd->fns;
    if (fns->ADIOI_xxx_ReadStridedColl == ADIOI_GEN_ReadStridedColl ||
        fd->file_system == ADIO_TESTFS )
    {
        return 1;
    }
    return 0;
}

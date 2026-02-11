SetGeoTransform( double * padfTransform )
{
    if( !SupportsInstr(INSTR_SetGeoTransform) )
        return GDALPamDataset::SetGeoTransform(padfTransform);

    CLIENT_ENTER();
    if( !GDALPipeWrite(p, INSTR_SetGeoTransform) ||
        !GDALPipeWrite(p, 6 * sizeof(double), padfTransform) )
        return CE_Failure;
    return CPLErrOnlyRet(p);
}

AdviseRead( int nXOff, int nYOff, int nXSize, int nYSize,
                                     int nBufXSize, int nBufYSize,
                                     GDALDataType eDT, char **papszOptions )
{
    if( !SupportsInstr(INSTR_Band_AdviseRead) )
        return GDALPamRasterBand::AdviseRead(nXOff, nYOff, nXSize, nYSize,
                                             nBufXSize, nBufYSize,
                                             eDT, papszOptions);

    CLIENT_ENTER();
    if( !WriteInstr(INSTR_Band_AdviseRead) ||
        !GDALPipeWrite(p, nXOff) ||
        !GDALPipeWrite(p, nYOff) ||
        !GDALPipeWrite(p, nXSize) ||
        !GDALPipeWrite(p, nYSize) ||
        !GDALPipeWrite(p, nBufXSize) ||
        !GDALPipeWrite(p, nBufYSize) ||
        !GDALPipeWrite(p, eDT) ||
        !GDALPipeWrite(p, papszOptions) )
        return CE_Failure;
    return CPLErrOnlyRet(p);
}

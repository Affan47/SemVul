SetColorInterpretation(GDALColorInterp eInterp)
{
    if( !SupportsInstr(INSTR_Band_SetColorInterpretation) )
        return GDALPamRasterBand::SetColorInterpretation(eInterp);

    CLIENT_ENTER();
    if( !WriteInstr(INSTR_Band_SetColorInterpretation) ||
        !GDALPipeWrite(p, eInterp) )
        return CE_Failure;
    return CPLErrOnlyRet(p);
}

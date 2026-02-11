GetJoules(int fdser, int yAddress)
{
    int nCnt;
    unsigned long Joules;

    strcpy(szSerBuffer, _clearCMD);
    szSerBuffer[cAddress] = yAddress;
    szSerBuffer[cCommand] = opGetEnergy10Sec;
    szSerBuffer[cCommandEnd] = '\0';
    nCnt = Communicate(fdser, yAddress);
    if (nCnt > 0 && TransState((int)szSerBuffer[aState],_opGetEnergy10Sec)) {
        Joules = szCvrtShort(szSerBuffer);
        if (bVerbose) fprintf(stderr, "Joules       %12lu\n",(unsigned long)Joules);
        fprintf(outfp, "\nEnergy in the last 10 seconds (Joules) : %lu\n",(unsigned long)Joules);
        return(0);
   }
    return(-1);
}

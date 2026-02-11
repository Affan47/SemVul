GetVerFW(int fdser, int yAddress)
{
    int nCnt;

    strcpy(szSerBuffer, _clearCMD);
    szSerBuffer[cAddress] = yAddress;
    szSerBuffer[cCommand] = opGetVerFW;
    szSerBuffer[cCommandEnd] = '\0';
    nCnt = Communicate(fdser, yAddress);
    if (nCnt > 0 && TransState((int)szSerBuffer[aState],_opGetVerFW)) {
        fprintf(outfp, "\nFirmware: %c.%c.%c.%c\n",szSerBuffer[aRel3],szSerBuffer[aRel2],szSerBuffer[aRel1],szSerBuffer[aRel0]);
        return(0);
   }
    return(-1);
}

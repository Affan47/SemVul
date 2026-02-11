GetConf(int fdser, int yAddress)
{
    int nCnt;

    strcpy(szSerBuffer, _clearCMD);
    szSerBuffer[cAddress] = yAddress;
    szSerBuffer[cCommand] = opGetConfig;
    szSerBuffer[cCommandEnd] = '\0';
    nCnt = Communicate(fdser, yAddress);
    crcValue = crc16(szSerBuffer, 8);
    if (nCnt > 0 && TransState((int)szSerBuffer[aState],_opGetConfig)) {
        switch (szSerBuffer[aConfCode]) {
            case ConfCode0:	fprintf(outfp, "\n%s\n",_ConfCode0); break;
            case ConfCode1:	fprintf(outfp, "\n%s\n",_ConfCode1); break;
            case ConfCode2:	fprintf(outfp, "\n%s\n",_ConfCode2); break;
            default:        break;
        }
        return(0);
    }
    return(-1);
}

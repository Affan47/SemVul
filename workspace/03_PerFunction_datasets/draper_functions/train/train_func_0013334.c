szCvrtShort(char *Buffer)
{
    unsigned char cValue[4];
    unsigned long *value;

    cValue[0] = Buffer[aParam2] & 0xff;
    cValue[1] = Buffer[aParam1] & 0xff;
    cValue[2] = 0x00;
    cValue[3] = 0x00;

    value = (unsigned long *)cValue;
    if (bVerbose) fprintf(stderr, "szCvrtShort  %12lu 0x%02x%02x%02x%02x\n",*value & 0xffff,cValue[3],cValue[2],cValue[1],cValue[0]);

    return(*value & 0xffff);
}

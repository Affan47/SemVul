writeVdsetTerminator(VolInfo* volInfo)
{
    int rc;
    unsigned char byte;
    unsigned char aString[6];


    byte = 255;
    rc = write711(volInfo, byte);
    if(rc <= 0)
        return rc;


    strcpy((char*)aString, "CD001");
    rc = wcWrite(volInfo, (char*)aString, 5);
    if(rc <= 0)
        return rc;


    byte = 1;
    rc = write711(volInfo, byte);
    if(rc <= 0)
        return rc;

    rc = writeByteBlock(volInfo, 0, 2041);
    if(rc < 0)
        return rc;

    return 1;
}

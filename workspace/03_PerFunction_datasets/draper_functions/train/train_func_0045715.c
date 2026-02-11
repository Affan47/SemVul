I2CWriteData(reader* globalData, uchar socket, ushort address,
                        uchar* data, int len, uchar* outBuffer, int *outBufLen) {
    int retVal = ASE_OK, counter = 0, writeLen = len;
    uchar cmdCode = 0, thisWrite;

    cmdCode = 0xA0;

    while (counter < len && retVal == ASE_OK) {
        thisWrite = (writeLen > MEM_CARD_WRITE_CHUNK_SIZE ? MEM_CARD_WRITE_CHUNK_SIZE : writeLen);
        retVal = I2CExecOutCommand(globalData, socket, cmdCode,
                                   address + counter, data + counter, thisWrite,
                                   outBuffer, outBufLen);
        counter += thisWrite;
        writeLen -= thisWrite;
    }

    if (retVal < 0)
        retVal = MEM_CARD_WRITE_FAILED;

    AddSW1SW2(retVal, outBuffer, outBufLen, 0);

    return ASE_OK;
}

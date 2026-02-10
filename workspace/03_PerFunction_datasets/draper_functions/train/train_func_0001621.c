Upload(const unsigned char * buffer, unsigned long size, unsigned long address) {
        unsigned long c=0;

        if (InitGSComms()) return 1;

        ReadWriteByte(2);
        ReadWrite32(address);
        ReadWrite32(size);

        for (c=0; c < size; c++) ReadWriteByte(buffer[c]);

        for (c=0; c < 8; c++) ReadWriteByte(0);

        if (CloseGSComms()) return 1;

        return 0;
}

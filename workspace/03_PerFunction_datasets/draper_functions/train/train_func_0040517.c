UploadFile(FILE * infile, unsigned long address) {
        unsigned long c=0;
        unsigned long size;
        char buf;

        if (fseek(infile,0,SEEK_END)) return 1;
        size=ftell(infile);
        rewind(infile);

        if (InitGSComms()) return 1;

    printf("Uploading File to %x | 00%%", (int)address);

    ReadWriteByte(2);
        ReadWrite32(address);
        ReadWrite32(size);

        for (c=0; c < size; c++) {
                fread(&buf,1,1,infile);
                if (c & 0x400) printf("\b\b\b%02lu%%", c*100/size);
                ReadWriteByte(buf);
        }

        for (c=0; c < 8; c++) ReadWriteByte(0);

        if (CloseGSComms()) return 1;

        printf("\b\b\bDone.\n");

        return 0;
}

unpackHtds()
{
    FILE *file, *out;
    char *filename, outfilename[16];
    int fileNo;
    unsigned long size;
    hNode *rootNode;
    int i, id;
    unsigned char dataByte, dataMask;
    unsigned char data[20864];
    unsigned char magic[4];

    id = 0;
    for (fileNo = 0; fileNo < 2; fileNo++)
    {
        filename = fileNo ? "allhtds2" : "allhtds1";
        file = fopen(filename, "rb");
        if (!file) die("Unable to open %s: %s\n", filename, strerror(errno));

        while (!feof(file))
        {

            size = read32(file);
            if (feof(file)) break;


            fread(magic, 4, 1, file);
            if (magic[0] != 'm' || magic[1] != 's' || magic[2] != 'q'
                    || magic[3] != fileNo)
                die ("Invalid file: %s\n", filename);


            dataByte = 0;
            dataMask = 0;
            rootNode = readHuffmanNode(file, &dataByte, &dataMask);


            memset(data, 0, sizeof(data));
            for (i = 0; i < size; i++)
            {
                data[i] = readHuffmanByte(file, rootNode, &dataByte, &dataMask);
            }


            for (i = 0; i < size; i += 16 * 16 / 2)
            {
                decodeVXOR(&data[i], 8, 16);
            }


            sprintf(outfilename, "tile%02i", id);
            out = fopen(outfilename, "wb");
            fwrite(data, 1, sizeof(data), out);
            fclose(out);


            freeHuffmanNode(rootNode);
            id++;
        }
        fclose(file);
    }
}

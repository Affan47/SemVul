getCodecDesc() const
    {
        CodecDesc desc;


        desc.fileType = "TIFF";


        desc.pixelTypes.resize(9);
        desc.pixelTypes[0] = "BILEVEL";
        desc.pixelTypes[1] = "UINT8";
        desc.pixelTypes[2] = "INT8";
        desc.pixelTypes[3] = "UINT16";
        desc.pixelTypes[4] = "INT16";
        desc.pixelTypes[5] = "UINT32";
        desc.pixelTypes[6] = "INT32";
        desc.pixelTypes[7] = "FLOAT";
        desc.pixelTypes[8] = "DOUBLE";


        desc.compressionTypes.resize(6);
        desc.compressionTypes[0] = "NONE";
        desc.compressionTypes[1] = "RLE";
        desc.compressionTypes[2] = "PACKBITS";
        desc.compressionTypes[3] = "JPEG";
        desc.compressionTypes[4] = "LZW";
        desc.compressionTypes[5] = "DEFLATE";


#if TIFFLIB_VERSION > 20070712
        desc.magicStrings.resize(3);
#else
        desc.magicStrings.resize(2);
#endif
        desc.magicStrings[0].resize(4);
        desc.magicStrings[0][0] = '\115';
        desc.magicStrings[0][1] = '\115';
        desc.magicStrings[0][2] = '\000';
        desc.magicStrings[0][3] = '\052';
        desc.magicStrings[1].resize(4);
        desc.magicStrings[1][0] = '\111';
        desc.magicStrings[1][1] = '\111';
        desc.magicStrings[1][2] = '\052';
        desc.magicStrings[1][3] = '\000';
#if TIFFLIB_VERSION > 20070712

        desc.magicStrings[2].resize(4);
        desc.magicStrings[2][0] = '\111';
        desc.magicStrings[2][1] = '\111';
        desc.magicStrings[2][2] = '\053';
        desc.magicStrings[2][3] = '\000';
#endif


        desc.fileExtensions.resize(2);
        desc.fileExtensions[0] = "tif";
        desc.fileExtensions[1] = "tiff";

        desc.bandNumbers.resize(4);
        desc.bandNumbers[0] = 1;
        desc.bandNumbers[1] = 2;
        desc.bandNumbers[2] = 3;
        desc.bandNumbers[3] = 4;

        return desc;
    }

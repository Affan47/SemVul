getCodecDesc() const
    {
        CodecDesc desc;


        desc.fileType = "SUN";


        desc.pixelTypes.resize(1);
        desc.pixelTypes[0] = "UINT8";


        desc.compressionTypes.resize(0);


        desc.magicStrings.resize(1);
        desc.magicStrings[0].resize(4);
        desc.magicStrings[0][0] = '\x59';
        desc.magicStrings[0][1] = '\xA6';
        desc.magicStrings[0][2] = '\x6A';
        desc.magicStrings[0][3] = '\x95';


        desc.fileExtensions.resize(1);
        desc.fileExtensions[0] = "ras";

        desc.bandNumbers.resize(2);
        desc.bandNumbers[0] = 1;
        desc.bandNumbers[1] = 3;

        return desc;
    }

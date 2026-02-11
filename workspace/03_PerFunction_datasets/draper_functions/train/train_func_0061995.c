WriteSCE(CoderInfo *coderInfo,
                    ChannelInfo *channelInfo,
                    BitStream *bitStream,
                    int objectType,
                    int writeFlag)
{
    int bits = 0;

#ifndef DRM
    if (writeFlag) {

        PutBit(bitStream, ID_SCE, LEN_SE_ID);


        PutBit(bitStream, channelInfo->tag, LEN_TAG);
    }

    bits += LEN_SE_ID;
    bits += LEN_TAG;
#endif


    bits += WriteICS(coderInfo, bitStream, 0, objectType, writeFlag);

    return bits;
}

diffTwoBytePrimaries(uint32_t p1, uint32_t p2, UBool isCompressible) {
    if((p1 & 0xff000000) == (p2 & 0xff000000)) {

        return (int32_t)(p2 - p1) >> 16;
    } else {
        int32_t linear1;
        int32_t linear2;
        int32_t factor;
        if(isCompressible) {

            linear1 = (int32_t)((p1 >> 16) & 0xff) - 4;
            linear2 = (int32_t)((p2 >> 16) & 0xff) - 4;
            factor = 251;
        } else {

            linear1 = (int32_t)((p1 >> 16) & 0xff) - 2;
            linear2 = (int32_t)((p2 >> 16) & 0xff) - 2;
            factor = 254;
        }
        linear1 += factor * (int32_t)((p1 >> 24) & 0xff);
        linear2 += factor * (int32_t)((p2 >> 24) & 0xff);
        return linear2 - linear1;
    }
}

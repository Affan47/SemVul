__initCRCTable() {
        static uint32_t res[256];

        for (int i = 0 ; i < 256 ; i++) {
            uint32_t c = i;
            for (int j = 0 ; j < 8 ; j++) {
                c = (c & 1) ? 0xedb88320 ^ (c >> 1) : c >> 1;
            }
            res[i] = c;
        }
        return res;
    }

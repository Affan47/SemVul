Decompress16(int compressionmode, const unsigned char* params,
                      int srcStep, int dstStep,
                      const unsigned char* pSrc, int16_t* pDst,
                      unsigned long currentframeoffset,
                      unsigned long copysamples)
    {
        switch (compressionmode) {
            case 0:
                pSrc += currentframeoffset * srcStep;
                while (copysamples) {
                    *pDst = get16(pSrc);
                    pDst += dstStep;
                    pSrc += srcStep;
                    copysamples--;
                }
                break;

            case 1:
                int y  = get16(params);
                int dy = get16(params + 2);
                while (currentframeoffset) {
                    dy -= int8_t(*pSrc);
                    y  -= dy;
                    pSrc += srcStep;
                    currentframeoffset--;
                }
                while (copysamples) {
                    dy -= int8_t(*pSrc);
                    y  -= dy;
                    *pDst = y;
                    pDst += dstStep;
                    pSrc += srcStep;
                    copysamples--;
                }
                break;
        }
    }

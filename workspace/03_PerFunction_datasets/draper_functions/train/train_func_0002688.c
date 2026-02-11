update()
  {
    const uint8_t *src1 = reinterpret_cast<const uint8_t*>(in1);
    const uint8_t *src2 = reinterpret_cast<const uint8_t*>(in2);
    uint8_t *dst = reinterpret_cast<uint8_t*>(out);
    uint32_t sizeCounter = size;

    uint32_t b, tmp;

    while (sizeCounter--)
      {
        for (b = 0; b < ALPHA; b++)
          {
            tmp = src1[b] << 8;
            tmp /= 256 - src2[b];
            dst[b] = MAX255(tmp);
          }

        dst[ALPHA] = MIN (src1[ALPHA], src2[ALPHA]);

        src1 += NBYTES;
        src2 += NBYTES;
        dst += NBYTES;
      }
  }

}

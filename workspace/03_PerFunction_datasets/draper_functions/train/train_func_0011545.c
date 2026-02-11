DesRawProcessBlock(word32* lIn, word32* rIn, const word32* kptr)
{
    word32 l = *lIn, r = *rIn, i;

    for (i=0; i<8; i++)
    {
        word32 work = rotrFixed(r, 4U) ^ kptr[4*i+0];
        l ^= Spbox[6][(work) & 0x3f]
          ^  Spbox[4][(work >> 8) & 0x3f]
          ^  Spbox[2][(work >> 16) & 0x3f]
          ^  Spbox[0][(work >> 24) & 0x3f];
        work = r ^ kptr[4*i+1];
        l ^= Spbox[7][(work) & 0x3f]
          ^  Spbox[5][(work >> 8) & 0x3f]
          ^  Spbox[3][(work >> 16) & 0x3f]
          ^  Spbox[1][(work >> 24) & 0x3f];

        work = rotrFixed(l, 4U) ^ kptr[4*i+2];
        r ^= Spbox[6][(work) & 0x3f]
          ^  Spbox[4][(work >> 8) & 0x3f]
          ^  Spbox[2][(work >> 16) & 0x3f]
          ^  Spbox[0][(work >> 24) & 0x3f];
        work = l ^ kptr[4*i+3];
        r ^= Spbox[7][(work) & 0x3f]
          ^  Spbox[5][(work >> 8) & 0x3f]
          ^  Spbox[3][(work >> 16) & 0x3f]
          ^  Spbox[1][(work >> 24) & 0x3f];
    }

    *lIn = l; *rIn = r;
}

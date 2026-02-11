count9_10_11(const Word16 *values,
                         const Word16  width,
                         Word16       *bitCount)
{

  Word32 t0,t1,i;
  Word32 bc9_10;
  Word16 bc11,sc;

  bc9_10=0;
  bc11=0;
  sc=0;

  for(i=0;i<width;i+=2){

    t0=ABS(values[i+0]);
    t1=ABS(values[i+1]);


    bc9_10 += EXPAND(huff_ltab9_10[t0][t1]);
    bc11 = bc11 + huff_ltab11[t0][t1];


    sc = sc + (t0>0) + (t1>0);
  }
  bitCount[1]=INVALID_BITCOUNT;
  bitCount[2]=INVALID_BITCOUNT;
  bitCount[3]=INVALID_BITCOUNT;
  bitCount[4]=INVALID_BITCOUNT;
  bitCount[5]=INVALID_BITCOUNT;
  bitCount[6]=INVALID_BITCOUNT;
  bitCount[7]=INVALID_BITCOUNT;
  bitCount[8]=INVALID_BITCOUNT;
  bitCount[9]=extract_h(bc9_10) + sc;
  bitCount[10]=extract_l(bc9_10) + sc;
  bitCount[11]=bc11 + sc;

}

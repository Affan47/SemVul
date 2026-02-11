FDKaacEnc_count3_4_5_6_7_8_9_10_11(const SHORT *RESTRICT values,
                                     const INT  width,
                                     INT       *bitCount)
{

  INT i;
  INT bc3_4,bc5_6,bc7_8,bc9_10,bc11,sc;
  INT t0,t1,t2,t3;

  bc3_4=0;
  bc5_6=0;
  bc7_8=0;
  bc9_10=0;
  bc11=0;
  sc=0;

  for(i=0;i<width;i+=4){

    t0= values[i+0];
    t1= values[i+1];
    t2= values[i+2];
    t3= values[i+3];

    bc5_6+=FDKaacEnc_huff_ltab5_6[t0+4][t1+4];
    bc5_6+=FDKaacEnc_huff_ltab5_6[t2+4][t3+4];

    t0=fixp_abs(t0);
    t1=fixp_abs(t1);
    t2=fixp_abs(t2);
    t3=fixp_abs(t3);

    bc3_4+= FDKaacEnc_huff_ltab3_4[t0][t1][t2][t3];

    bc7_8+=FDKaacEnc_huff_ltab7_8[t0][t1];
    bc7_8+=FDKaacEnc_huff_ltab7_8[t2][t3];

    bc9_10+=FDKaacEnc_huff_ltab9_10[t0][t1];
    bc9_10+=FDKaacEnc_huff_ltab9_10[t2][t3];

    bc11+= (INT) FDKaacEnc_huff_ltab11[t0][t1];
    bc11+= (INT) FDKaacEnc_huff_ltab11[t2][t3];

    sc+=(t0>0)+(t1>0)+(t2>0)+(t3>0);
  }

  bitCount[1]=INVALID_BITCOUNT;
  bitCount[2]=INVALID_BITCOUNT;
  bitCount[3]=HI_LTAB(bc3_4)+sc;
  bitCount[4]=LO_LTAB(bc3_4)+sc;
  bitCount[5]=HI_LTAB(bc5_6);
  bitCount[6]=LO_LTAB(bc5_6);
  bitCount[7]=HI_LTAB(bc7_8)+sc;
  bitCount[8]=LO_LTAB(bc7_8)+sc;
  bitCount[9]=HI_LTAB(bc9_10)+sc;
  bitCount[10]=LO_LTAB(bc9_10)+sc;
  bitCount[11]=bc11+sc;
}

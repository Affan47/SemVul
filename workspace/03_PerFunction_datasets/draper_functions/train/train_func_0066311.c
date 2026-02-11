jpeg_fdct_2x4 (DCTELEM * data, JSAMPARRAY sample_data, JDIMENSION start_col)
{
  INT32 tmp0, tmp1;
  INT32 tmp10, tmp11;
  DCTELEM *dataptr;
  JSAMPROW elemptr;
  int ctr;
  SHIFT_TEMPS


  MEMZERO(data, SIZEOF(DCTELEM) * DCTSIZE2);


  dataptr = data;
  for (ctr = 0; ctr < 4; ctr++) {
    elemptr = sample_data[ctr] + start_col;


    tmp0 = GETJSAMPLE(elemptr[0]);
    tmp1 = GETJSAMPLE(elemptr[1]);


    dataptr[0] = (DCTELEM) ((tmp0 + tmp1 - 2 * CENTERJSAMPLE) << 3);


    dataptr[1] = (DCTELEM) ((tmp0 - tmp1) << 3);

    dataptr += DCTSIZE;
  }


  dataptr = data;
  for (ctr = 0; ctr < 2; ctr++) {


    tmp0 = dataptr[DCTSIZE*0] + dataptr[DCTSIZE*3];
    tmp1 = dataptr[DCTSIZE*1] + dataptr[DCTSIZE*2];

    tmp10 = dataptr[DCTSIZE*0] - dataptr[DCTSIZE*3];
    tmp11 = dataptr[DCTSIZE*1] - dataptr[DCTSIZE*2];

    dataptr[DCTSIZE*0] = (DCTELEM) (tmp0 + tmp1);
    dataptr[DCTSIZE*2] = (DCTELEM) (tmp0 - tmp1);


    tmp0 = MULTIPLY(tmp10 + tmp11, FIX_0_541196100);

    tmp0 += ONE << (CONST_BITS-1);

    dataptr[DCTSIZE*1] = (DCTELEM)
      RIGHT_SHIFT(tmp0 + MULTIPLY(tmp10, FIX_0_765366865),
		  CONST_BITS);
    dataptr[DCTSIZE*3] = (DCTELEM)
      RIGHT_SHIFT(tmp0 - MULTIPLY(tmp11, FIX_1_847759065),
		  CONST_BITS);

    dataptr++;
  }
}

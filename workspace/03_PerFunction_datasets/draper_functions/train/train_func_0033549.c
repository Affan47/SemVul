vthr_vec_StringVal(struct __vpiVThrVec*rfp, s_vpi_value*vp)
{
    char tmp = 0;
    char *rbuf = need_result_buf((rfp->wid / 8) + 1, RBUF_VAL);
    char *cp = rbuf;

    for(int bitnr=rfp->wid-1; bitnr>=0; bitnr--){
	tmp <<= 1;

	switch(get_bit(rfp, bitnr)){
	  case BIT4_0:
	      break;
	  case BIT4_1:
	      tmp |= 1;
	      break;
	  default:
	      break;
	}

	if ((bitnr&7)==0){

	      if (tmp == 0 && cp == rbuf)
		    continue;


	      *cp++ = tmp? tmp : ' ';
	      tmp = 0;
	}
    }
    *cp++ = 0;
    vp->value.str = rbuf;
    return;
}

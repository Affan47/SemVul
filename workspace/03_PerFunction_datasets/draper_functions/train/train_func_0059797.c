check_param_coherence(HTK_HMM_INFO *hmm, HTK_Param *pinfo)
{
  boolean ret_flag;

  ret_flag = TRUE;


  if (hmm->opt.param_type
      != (pinfo->header.samptype & ~(F_COMPRESS | F_CHECKSUM))) {


    ret_flag = FALSE;
  }


  if (hmm->opt.vec_size != pinfo->veclen) {


    ret_flag = FALSE;
  }

  return(ret_flag);
}

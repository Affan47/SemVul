HCPcdeflate_seek(accrec_t * access_rec, int32 offset, int origin)
{
    CONSTR(FUNC, "HCPcdeflate_seek");
    compinfo_t *info;
    comp_coder_deflate_info_t *deflate_info;
    uint8      tmp_buf[DEFLATE_TMP_BUF_SIZE];


    origin = origin;

    info = (compinfo_t *) access_rec->special_info;
    deflate_info = &(info->cinfo.coder_info.deflate_info);


    if(deflate_info->acc_init==0)
      {
        if (HCIcdeflate_staccess2(access_rec, DFACC_READ) == FAIL)
            HRETURN_ERROR(DFE_CINIT, FAIL);
      }

    if (offset < deflate_info->offset)
      {
#ifdef OLD_WAY

          if (deflateReset(&(deflate_info->deflate_context))!=Z_OK)
              HRETURN_ERROR(DFE_CINIT, FAIL);
#else

        if (HCIcdeflate_term(info, deflate_info->acc_mode) == FAIL)
            HRETURN_ERROR(DFE_CTERM, FAIL);


        if (HCIcdeflate_staccess2(access_rec, DFACC_READ) == FAIL)
            HRETURN_ERROR(DFE_CINIT, FAIL);

#endif


          if(Hseek(info->aid,0,0)==FAIL)
              HRETURN_ERROR(DFE_SEEKERROR, FAIL);
      }

#ifdef OLD_WAY
    if ((tmp_buf = (uint8 *) HDmalloc(DEFLATE_TMP_BUF_SIZE)) == NULL)
        HRETURN_ERROR(DFE_NOSPACE, FAIL);
#endif

    while (deflate_info->offset + DEFLATE_TMP_BUF_SIZE < offset) {
        if (HCIcdeflate_decode(info, DEFLATE_TMP_BUF_SIZE, tmp_buf) == FAIL)
          {
#ifdef OLD_WAY
              HDfree(tmp_buf);
#endif
              HRETURN_ERROR(DFE_CDECODE, FAIL)
          }
      }
    if (deflate_info->offset < offset) {
        if (HCIcdeflate_decode(info, offset - deflate_info->offset, tmp_buf) == FAIL)
          {
#ifdef OLD_WAY
              HDfree(tmp_buf);
#endif
              HRETURN_ERROR(DFE_CDECODE, FAIL)
          }
      }

#ifdef OLD_WAY
    HDfree(tmp_buf);
#endif
    return (SUCCEED);
}

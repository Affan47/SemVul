HCPencode_header(uint8 *p, comp_model_t model_type, model_info * m_info,
         comp_coder_t coder_type, comp_info * c_info)
{
    CONSTR(FUNC, "HCPencode_header");
    int32 ret_value=SUCCEED;


    HEclear();
    if (p==NULL || m_info==NULL || c_info==NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    UINT16ENCODE(p, (uint16) model_type);
    UINT16ENCODE(p, (uint16) coder_type);


    switch (model_type)
      {
          default:
              break;
      }


    switch (coder_type)
      {
          case COMP_CODE_NBIT:

              INT32ENCODE(p, c_info->nbit.nt);

              UINT16ENCODE(p, (uint16) c_info->nbit.sign_ext);

              UINT16ENCODE(p, (uint16) c_info->nbit.fill_one);

              INT32ENCODE(p, (int32) c_info->nbit.start_bit);

              INT32ENCODE(p, (int32) c_info->nbit.bit_len);
              break;

          case COMP_CODE_SKPHUFF:
              if(c_info->skphuff.skp_size<1)
                  HRETURN_ERROR(DFE_BADCODER, FAIL)


              UINT32ENCODE(p, (uint32) c_info->skphuff.skp_size);

              UINT32ENCODE(p, (uint32) c_info->skphuff.skp_size);
              break;

          case COMP_CODE_DEFLATE:


              if(c_info->deflate.level<0 || c_info->deflate.level>9)
                  HRETURN_ERROR(DFE_BADCODER, FAIL)


              UINT16ENCODE(p, (uint16) c_info->deflate.level);
              break;

          case COMP_CODE_SZIP:
              UINT32ENCODE(p, (uint32) c_info->szip.pixels);
              UINT32ENCODE(p, (uint32) c_info->szip.pixels_per_scanline);
              UINT32ENCODE(p, (uint32) (c_info->szip.options_mask | SZ_H4_REV_2));
              *p++ = (uint8) c_info->szip.bits_per_pixel;
              *p++ = (uint8) c_info->szip.pixels_per_block;
              break;

          case COMP_CODE_IMCOMP:
              HRETURN_ERROR(DFE_BADCODER, FAIL);
              break;

          default:
              break;
      }

done:
    if(ret_value == FAIL)
      {

      }


    return ret_value;
}

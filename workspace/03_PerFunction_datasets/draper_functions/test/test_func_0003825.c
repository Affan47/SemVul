jpeg_CreateCompress (j_compress_ptr cinfo, int version, size_t structsize)
{
  int i;


  cinfo->mem = NULL;
  if (version != JPEG_LIB_VERSION)
    ERREXIT2(cinfo, JERR_BAD_LIB_VERSION, JPEG_LIB_VERSION, version);
  if (structsize != SIZEOF(struct jpeg_compress_struct))
    ERREXIT2(cinfo, JERR_BAD_STRUCT_SIZE,
	     (int) SIZEOF(struct jpeg_compress_struct), (int) structsize);


  {
    struct jpeg_error_mgr * err = cinfo->err;
    void * client_data = cinfo->client_data;
    MEMZERO(cinfo, SIZEOF(struct jpeg_compress_struct));
    cinfo->err = err;
    cinfo->client_data = client_data;
  }
  cinfo->is_decompressor = FALSE;


  jinit_memory_mgr((j_common_ptr) cinfo);


  cinfo->progress = NULL;
  cinfo->dest = NULL;

  cinfo->comp_info = NULL;

  for (i = 0; i < NUM_QUANT_TBLS; i++)
    cinfo->quant_tbl_ptrs[i] = NULL;

  for (i = 0; i < NUM_HUFF_TBLS; i++) {
    cinfo->dc_huff_tbl_ptrs[i] = NULL;
    cinfo->ac_huff_tbl_ptrs[i] = NULL;
  }

  cinfo->script_space = NULL;

  cinfo->input_gamma = 1.0;


  cinfo->global_state = CSTATE_START;
}

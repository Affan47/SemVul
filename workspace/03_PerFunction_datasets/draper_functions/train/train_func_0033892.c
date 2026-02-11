GR2bmapped(int32 riid, intn *tobe_mapped, intn *name_generated)
{
    CONSTR(FUNC, "GR2bmapped");
    ri_info_t *ri_ptr;
    intn   should_map = FALSE;
    uint16 img_tag, img_ref;
    int32  ritype;
    intn   special_type=0;
    int32  file_id;
    intn   status;
    intn   ret_value = SUCCEED;


    HEclear();


    if (HAatom_group(riid) != RIIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);


    ri_ptr = (ri_info_t *) HAatom_object(riid);
    if (NULL == ri_ptr)
        HGOTO_ERROR(DFE_RINOTFOUND, FAIL);


    img_tag = ri_ptr->img_tag;
    img_ref = ri_ptr->img_ref;
    file_id = ri_ptr->gr_ptr->hdf_file_id;


    if (img_tag == DFTAG_RI8 || img_tag == DFTAG_CI8)
    {
	if (ri_ptr->img_dim.comp_tag == DFTAG_RLE ||
	    ri_ptr->img_dim.comp_tag == DFTAG_NULL)
	    should_map = TRUE;
    }


    else if (img_tag == DFTAG_RI || img_tag == DFTAG_CI)
    {

	status = GRgetiminfo(riid, NULL, NULL, &ritype, NULL, NULL, NULL);


	if (ritype == DFNT_UCHAR8 || ritype == DFNT_CHAR8 ||
	    ritype == DFNT_UINT8 || ritype == DFNT_INT8)
	{

	    if (ri_ptr->img_dim.ncomps ==1)
	    {

		comp_coder_t comp_type=COMP_CODE_NONE;
		status = GRgetcomptype(riid, &comp_type);
		if (comp_type == COMP_CODE_RLE || comp_type == COMP_CODE_NONE)
		{
		    special_type = GRIisspecial_type(file_id, img_tag, img_ref);


		    if (special_type == SPECIAL_COMP || special_type == 0)
			should_map = TRUE;
		}
	    }
	}
    }

    *tobe_mapped = should_map;


    *name_generated = ri_ptr->name_generated;

done:
  if(ret_value == 0)
    {
    }

  return ret_value;
}

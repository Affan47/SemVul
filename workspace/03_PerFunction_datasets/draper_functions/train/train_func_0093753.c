SDgetcompress(int32     id,
              comp_coder_t*    comp_type,
              comp_info* c_info)

{
    CONSTR(FUNC, "SDgetcompress");
    NC        *handle;
    NC_var    *var;
    intn       status = FAIL;
    intn       ret_value = SUCCEED;

#ifdef SDDEBUG
    fprintf(stderr, "SDgetcompress: I've been called\n");
#endif


    HEclear();

    if(comp_type == NULL || c_info == NULL)
	HGOTO_ERROR(DFE_ARGS, FAIL);

    handle = SDIhandle_from_id(id, SDSTYPE);
    if(handle == NULL || handle->file_type != HDF_FILE)
	HGOTO_ERROR(DFE_ARGS, FAIL);
    if(handle->vars == NULL)
	HGOTO_ERROR(DFE_ARGS, FAIL);

    var = SDIget_var(handle, id);
    if(var == NULL) HGOTO_ERROR(DFE_ARGS, FAIL);

#ifdef SDDEBUG
    printf("SDgetcompress(): var->data_ref=%d, var->aid=%d\n",(int)var->data_ref, (int)var->aid);
#endif
    if(!var->data_ref)
	HGOTO_ERROR(DFE_ARGS, FAIL);


    status = HCPgetcompress(handle->hdf_file, var->data_tag, var->data_ref,
		comp_type, c_info);
    if(status==FAIL) HGOTO_ERROR(DFE_INTERNAL, FAIL);

done:
    if (ret_value == FAIL)
      {

      }


    return ret_value;
}

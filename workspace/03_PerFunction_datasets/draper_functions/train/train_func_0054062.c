SDdiminfo(int32  id,
          char  *name,
          int32 *size,
          int32 *nt,
          int32 *nattr  )
{
    NC      *handle = NULL;
    NC_dim  *dim = NULL;
    NC_var   *var = NULL;
    NC_var **dp = NULL;
    intn     ii;
    intn     len;
    int32    varid;
    int      ret_value = SUCCEED;

#ifdef SDDEBUG
    fprintf(stderr, "SDdiminfo: I've been called\n");
#endif


    HEclear();

    handle = SDIhandle_from_id(id, DIMTYPE);
    if(handle == NULL)
      {
          ret_value = FAIL;
          goto done;
      }

    if(handle->dims == NULL)
      {
          ret_value = FAIL;
          goto done;
      }

    dim = SDIget_dim(handle, id);
    if(dim == NULL)
      {
          ret_value = FAIL;
          goto done;
      }

    if(name != NULL)
      {
#if 0
        HDstrncpy(name, dim->name->values, dim->name->len);
#endif
        HDmemcpy(name, dim->name->values, dim->name->len);
        name[dim->name->len] = '\0';
      }
    else
        name = dim->name->values;


    *size = dim->size;


    *nt    = 0;
    *nattr = 0;


    if(handle->vars)
      {
          len = dim->name->len;
          dp = (NC_var**)handle->vars->values;
          for(ii = 0 ; ii < handle->vars->count ; ii++, dp++)
            {

	      if((*dp)->assoc->count == 1)
	      {

                 if( len == (*dp)->name->len
                    && HDstrncmp(name, (*dp)->name->values, (*dp)->name->len) == 0)
		 {
		    if (handle->file_type == HDF_FILE)
		    {


			if ((*dp)->var_type == IS_CRDVAR ||
			    (*dp)->var_type == UNKNOWN)
			{
			    *nt = ((*dp)->numrecs ? (*dp)->HDFtype : 0);
			    *nattr = ((*dp)->attrs ? (*dp)->attrs->count : 0);
			    goto done;
			}
		    }
		    else
		    {
			*nt = (*dp)->HDFtype;
			*nattr = ((*dp)->attrs ? (*dp)->attrs->count : 0);
			goto done;
		    }
		 }
	      }
            }
      }
done:
    if (ret_value == FAIL)
      {

      }


    return ret_value;
}

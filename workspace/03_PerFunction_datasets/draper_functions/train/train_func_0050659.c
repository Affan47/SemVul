hdf_write_dim(XDR *xdrs, NC *handle, NC_dim **dim, int32 cnt)
{
    int32 tags[100];
    int32 refs[100];
    int32 count;
    const char  *class = NULL;
    char  name[H4_MAX_NC_NAME] = "";
    int32 ret_value = SUCCEED;

#if DEBUG
    fprintf(stderr, "hdf_write_dim I've been called\n");
    fprintf(stderr, "The name is -- %s -- \n", (*dim)->name->values);
#endif


    count = 0;
    tags[count] = DFTAG_VH;
    refs[count] = hdf_create_dim_vdata(xdrs, handle, (*dim));
    if(refs[count] == FAIL)
      {
          ret_value = FAIL;
          goto done;
      }
    count++;


    if ((*dim)->dim00_compat)
      {
          tags[count] = DFTAG_VH;
          refs[count] = hdf_create_compat_dim_vdata(xdrs, handle, (*dim), DIMVAL_VERSION00);
          if(refs[count] == FAIL)
            {
                ret_value = FAIL;
                goto done;
            }
          count++;
      }


    if((*dim)->size == NC_UNLIMITED)
        class = _HDF_UDIMENSION;
    else
        class = _HDF_DIMENSION;

    if(HDstrncmp((*dim)->name->values, "fakeDim", 7) == 0)
        sprintf(name, "fakeDim%d", (int)cnt);
    else
        HDstrcpy(name, (*dim)->name->values);


    (*dim)->vgid = VHmakegroup(handle->hdf_file, tags, refs, count,
                               name, class);

    ret_value = (*dim)->vgid;

done:
    if (ret_value == FAIL)
      {

      }


    return ret_value;
}

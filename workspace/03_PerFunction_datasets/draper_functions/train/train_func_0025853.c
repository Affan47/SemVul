SDstart(const char *name,
        int32       HDFmode )
{
    CONSTR(FUNC, "SDstart");
    intn    cdfid;
    int32   fid;
    intn    NCmode;
    NC     *handle = NULL;
    int32   ret_value = SUCCEED;

#ifdef SDDEBUG
    fprintf(stderr, "SDstart: I've been called\n");
#endif


    HEclear();


    ncopts = 0;


    if (library_terminate == FALSE)
        if(SDIstart()==FAIL)
            HGOTO_ERROR(DFE_CANTINIT, FAIL);


    if(HDFmode & DFACC_WRITE)
        NCmode = NC_RDWR;
    else
        NCmode = NC_NOWRITE;

    if(HDFmode & DFACC_CREATE)
      {
        if(!SDI_can_clobber(name))
            HGOTO_ERROR(DFE_DENIED, FAIL);
        cdfid = nccreate(name, NC_CLOBBER);
      }
    else
      {
        cdfid = ncopen(name, NCmode);
      }


    if(cdfid == -1)
    {


        int16 err = HEvalue(1);
        HGOTO_ERROR(err, FAIL);
    }


    handle = NC_check_id(cdfid);
    if(handle == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);


    handle->flags &= ~(NC_INDEF);


    fid = (((int32) cdfid) << 20) + (((int32) CDFTYPE) << 16) + cdfid;

    ret_value = fid;

done:
    if (ret_value == FAIL)
      {

      }


    return ret_value;
}

nc4_file_list_add(NC_FILE_INFO_T** ncp, NC_Dispatch* dispatch)
{
    NC_FILE_INFO_T *nc;
    int status = NC_NOERR;


    status = dispatch->new_nc((NC**)&nc);
    if(status) return status;


    if ((status = add_to_NCList((NC *)nc)))
    {
       if(nc && nc->ext_ncid > 0)
       {
          del_from_NCList((NC *)nc);
          free(nc);
       }
       return status;
    }


    if(ncp)
       *ncp = nc;

    return NC_NOERR;
}

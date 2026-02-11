HIrelease_filerec_node(filerec_t *file_rec)
{
#ifdef LATER
    CONSTR(FUNC, "HIrelease_filerec_node");
#endif


    if(file_rec->file!=NULL)
	HI_CLOSE(file_rec->file);


    if(file_rec->path!=NULL)
        HDfree(file_rec->path);
    HDfree(file_rec);

#ifdef LATER
done:
  if(ret_value == FAIL)
    {

    }
#endif


  return SUCCEED;
}

GRgetiminfo(int32 riid,char *name,int32 *ncomp,int32 *nt,int32 *il,
    int32 dimsizes[2],int32 *n_attr)
{
    CONSTR(FUNC, "GRgetiminfo");
    ri_info_t *ri_ptr;
    intn  ret_value = SUCCEED;


    HEclear();


    if (HAatom_group(riid)!=RIIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);


    if (NULL == (ri_ptr = (ri_info_t *) HAatom_object(riid)))
        HGOTO_ERROR(DFE_RINOTFOUND, FAIL);

    if(name!=NULL)
        HDstrcpy(name, ri_ptr->name);

    if(ncomp!=NULL)
        *ncomp=ri_ptr->img_dim.ncomps;

    if(nt!=NULL)
        *nt=ri_ptr->img_dim.nt;

    if(il!=NULL)
        *il=(int32)ri_ptr->img_dim.il;

    if(dimsizes!=NULL)
      {
          dimsizes[0]=ri_ptr->img_dim.xdim;
          dimsizes[1]=ri_ptr->img_dim.ydim;
      }

    if(n_attr!=NULL)
        *n_attr=ri_ptr->lattr_count;

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}

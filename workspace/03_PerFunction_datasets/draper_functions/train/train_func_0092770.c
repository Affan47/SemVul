HULcreate_list(HULfind_func_t find_func
)
{
    CONSTR(FUNC, "HULcreate_list");
    list_head_t *ret_value=NULL;

    HEclear();


    if((ret_value=(list_head_t *)HDcalloc(1,sizeof(list_head_t)))==NULL)
        HGOTO_ERROR(DFE_NOSPACE, NULL);


    ret_value->count=0;


    if(find_func==NULL)
        ret_value->flags=HUL_UNSORTED_LIST;
    else
        ret_value->flags=HUL_SORTED_LIST;
    ret_value->cmp_func=find_func;

done:
  if(ret_value == NULL)
    {

    }


  return ret_value;
}

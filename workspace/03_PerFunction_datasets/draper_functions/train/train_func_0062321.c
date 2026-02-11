DAset_elem(dynarr_p arr_ptr,
    intn elem,
    VOIDP obj
)
{
    CONSTR(FUNC, "DAset_elem");
    dynarr_t   *arr;
    intn        ret_value=SUCCEED;

    HEclear();
    arr=(dynarr_t *)arr_ptr;
    if(elem<0 || arr==NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    if(elem>=arr->num_elems)
      {
        intn new_size;

        new_size=((elem/arr->incr_mult)+1)*arr->incr_mult;
        if(arr->num_elems==0)
          {
            if((arr->arr=(VOIDP *)HDcalloc(new_size,sizeof(VOIDP)))==NULL)
                HGOTO_ERROR(DFE_NOSPACE, FAIL);
          }
        else
          {
            VOIDP *new_arr;

            if((new_arr=(VOIDP *)HDrealloc(arr->arr,new_size*sizeof(VOIDP)))==NULL)
                HGOTO_ERROR(DFE_NOSPACE, FAIL);
            HDmemset(&new_arr[arr->num_elems],0,sizeof(VOIDP)*(uintn)(new_size-arr->num_elems));
            arr->arr=new_arr;
          }
        arr->num_elems=new_size;
      }


    arr->arr[elem]=obj;

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}

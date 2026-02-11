HAdestroy_group(group_t grp
)
{
    CONSTR(FUNC, "HAdestroy_group");
    atom_group_t *grp_ptr=NULL;
    intn ret_value=SUCCEED;

    HEclear();
    if(grp<=BADGROUP || grp>=MAXGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    grp_ptr=atom_group_list[grp];
    if(grp_ptr==NULL || grp_ptr->count<=0)
        HGOTO_ERROR(DFE_INTERNAL, FAIL);


    if((--(grp_ptr->count))==0)
      {
#ifdef ATOMS_ARE_CACHED
      {
        uintn i;

        for(i=0; i<ATOM_CACHE_SIZE; i++)
            if(ATOM_TO_GROUP(atom_id_cache[i])==grp)
              {
                atom_id_cache[i]=(-1);
                atom_obj_cache[i]=NULL;
              }
      }
#endif
        HDfree(grp_ptr->atom_list);
	grp_ptr->atom_list = NULL;
      }

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}

HTIunregister_tag_ref(filerec_t * file_rec, dd_t *dd_ptr)
{
  CONSTR(FUNC, "HTIunregister_tag_ref");
  tag_info *tinfo_ptr;
  tag_info **tip_ptr;
  uint16 base_tag=BASETAG(dd_ptr->tag);
  int         ret_value = SUCCEED;

  HEclear();

  if((tip_ptr=(tag_info **)tbbtdfind(file_rec->tag_tree,(VOIDP)&base_tag,NULL))==NULL)
    {
      HGOTO_ERROR(DFE_BADTAG, FAIL);
    }
  else
    {
        intn ref_bit;

        tinfo_ptr=*tip_ptr;
        if((ref_bit=bv_get(tinfo_ptr->b,(intn)dd_ptr->ref))==FAIL)
            HGOTO_ERROR(DFE_BVGET, FAIL);
        if(ref_bit==BV_FALSE)
            HGOTO_ERROR(DFE_INTERNAL, FAIL);
        if(bv_set(tinfo_ptr->b,(intn)dd_ptr->ref,BV_FALSE)==FAIL)
            HGOTO_ERROR(DFE_BVSET, FAIL);


        if(DAdel_elem(tinfo_ptr->d,(intn)dd_ptr->ref)==NULL)
            HGOTO_ERROR(DFE_INTERNAL, FAIL);


        dd_ptr->tag=DFTAG_NULL;
    }

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}

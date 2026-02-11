AssPlistDense (
    Obj                 list,
    Int                 pos,
    Obj                 val )
{
  Int len;


  CLEAR_FILTS_LIST(list);


  len = LEN_PLIST( list );
  if ( len < pos ) {
    GROW_PLIST( list, pos );
    SET_LEN_PLIST( list, pos );
  }


    SET_ELM_PLIST( list, pos, val );
    CHANGED_BAG( list );


    if (pos <= len+1)
      SET_FILT_LIST( list, FN_IS_DENSE );
    else
	SET_FILT_LIST( list, FN_IS_NDENSE );
}

SetupAttribute(Obj attr, Obj setter, Obj tester, Int flag2)
{
  Obj flags;


  FLAG1_FILT(attr)  = INTOBJ_INT( 0 );
  FLAG2_FILT(attr)  = INTOBJ_INT( flag2 );
  NEW_FLAGS( flags, flag2 );
  SET_LEN_FLAGS( flags, flag2 );
  SET_ELM_FLAGS( flags, flag2, True );


  FLAGS_FILT(attr) = FLAGS_FILT(tester);

  SETTR_FILT(attr)  = setter;
  TESTR_FILT(attr)  = tester;
  SET_ENABLED_ATTR(attr,1);
  CHANGED_BAG(attr);
  return;
}

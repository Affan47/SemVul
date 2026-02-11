MakeTester( Obj name, Int flag)
{
  Obj fname;
  Obj tester;
  Obj flags;
    fname = NEW_STRING( GET_LEN_STRING(name) + 8 );
    RetypeBag( fname, IMMUTABLE_TNUM(TNUM_OBJ(fname)) );
    SyStrncat( CSTR_STRING(fname), "Tester(", 7 );
    SyStrncat( CSTR_STRING(fname), CSTR_STRING(name), GET_LEN_STRING(name) );
    SyStrncat( CSTR_STRING(fname), ")", 1 );
    tester = NewFunctionT( T_FUNCTION, SIZE_OPER, fname, 1L, 0L,
                           DoTestAttribute );
    FLAG1_FILT(tester)  = INTOBJ_INT( 0 );
    FLAG2_FILT(tester)  = INTOBJ_INT( flag );
    NEW_FLAGS( flags, flag );
    SET_LEN_FLAGS( flags, flag );
    SET_ELM_FLAGS( flags, flag, True );
    FLAGS_FILT(tester)  = flags;
    SETTR_FILT(tester)  = 0;
    TESTR_FILT(tester)  = ReturnTrueFilter;
    CHANGED_BAG(tester);
    return tester;
}

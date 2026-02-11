Ins_WCVTF( INS_ARG )
  {
    int ov;

    if ( BOUNDS( args[0], CUR.cvtSize ) )
    {
      CUR.error = TT_Err_Invalid_Reference;
      return;
    }

    ov = CUR.cvt[args[0]];
    CUR.cvt[args[0]] = FUnits_To_Pixels( EXEC_ARGS args[1] );
    DBG_PRINT3(" cvt[%d]%d:=%d", args[0], ov, CUR.cvt[args[0]]);
  }

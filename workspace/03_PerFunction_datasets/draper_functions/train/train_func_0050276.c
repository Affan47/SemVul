VasyDriveVerilogFsm( RtlFigure )

  rtlfig_list *RtlFigure;
{
  rtlfsm_list      *RtlFsm;


  for ( RtlFsm  = RtlFigure->FSM;
        RtlFsm != (rtlfsm_list *)NULL;
        RtlFsm  = RtlFsm->NEXT )
  {
    VasyError( VASY_NOT_YET_IMPLEMENTED_ERROR, "Driver Verilog: FSM" );


  }
}

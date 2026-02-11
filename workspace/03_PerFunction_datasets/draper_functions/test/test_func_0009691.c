export_hkl_data( const HKL_data_base& cdata )
{
  if ( mode != WRITE )
    Message::message( Message_fatal( "PHSfile: export_hkl_data - no file open for write" ) );

  if      ( cdata.type() == data32::F_sigF::type()  ) f_sigf_o = &cdata;
  else if ( cdata.type() == data32::Phi_fom::type() ) phi_wt_o = &cdata;
  else
    Message::message( Message_fatal( "PHSfile: export_hkl_data - data must be F_sigF or Phi_fom" ) );
}

_program_unload (HpOption this, HpScsi scsi, HpOptSet optset, HpData data)
{
  hp_bool_t  adfscan = ( sanei_hp_optset_scan_type (optset, data)
                           == SCL_ADF_SCAN );


  if (adfscan)
  {int val;

   if ( sanei_hp_scl_inquire(scsi, SCL_ADF_RDY_UNLOAD, &val, 0, 0)
       == SANE_STATUS_GOOD )
   {
     DBG(3, "program_unload: ADF is%sready to unload\n", val ? " " : " not ");
   }
   else
   {
     DBG(3, "program_unload: Command 'Ready to unload' not supported\n");
   }
  }
  return hp_option_download(this, data, optset, scsi);
}

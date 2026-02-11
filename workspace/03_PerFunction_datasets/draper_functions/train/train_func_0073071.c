gap_gve_misc_do_master_encoder_progress(GapGveMasterEncoderStatus *encStatus)
{
  if(encStatus)
  {
    encStatus->pidOfRunningEncoder = gap_base_getpid();
    p_write_encoder_status(encStatus);
  }
}

xsh_instrument_nir_corr_if_JH(cpl_frameset* raws, xsh_instrument* instr)
{
  cpl_frame* frame=NULL;

  frame=cpl_frameset_get_frame(raws,0);

  if(instr->arm == XSH_ARM_NIR) {

    if(xsh_instrument_nir_is_JH(frame,instr)) {
       instr->config->order_min=13;
       instr->config->order_max=26;
       instr->config->orders=14;
    }

  }

  return cpl_error_get_code();
}

coff_close_file(void)
{

  if(!state.obj.enabled)
    return;


  _update_section_size();


  _update_reloc_ptr();


  gp_cofflink_combine_overlay(state.obj.object, 1);

  _copy_config();

  if (gp_write_coff(state.obj.object, (state.num.errors + gp_num_errors)) == 1)
    gperror(GPE_UNKNOWN, "system error while writing object file");

  gp_coffgen_free(state.obj.object);
}

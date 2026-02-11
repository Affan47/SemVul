_do_pagesel(gpasmVal r,
		           char *name,
		           int arity,
		           struct pnode *parms,
		           unsigned short reloc_type)
{
  struct pnode *p;
  int address;
  int page;
  int num_reloc;
  int use_wreg = 0;

  if ((reloc_type == RELOCT_PAGESEL_WREG) ||
      (state.device.class == PROC_CLASS_PIC16)) {
    use_wreg = 1;
  }

  if ((state.device.class == PROC_CLASS_EEPROM8) ||
      (state.device.class == PROC_CLASS_EEPROM16) ||
      (state.device.class == PROC_CLASS_PIC16E)) {

    return r;
  } else if (state.device.class == PROC_CLASS_PIC16) {
    gpmessage(GPM_W_MODIFIED, NULL);
  }

  if (enforce_arity(arity, 1)) {
    p = HEAD(parms);
    if (state.mode == absolute) {
      address = maybe_evaluate(p);
      page = gp_processor_check_page(state.device.class, address);
      state.org += gp_processor_set_page(state.device.class,
                                         state.processor_info->num_pages,
                                         page,
                                         state.i_memory,
                                         state.org,
                                         use_wreg);
    } else {
      num_reloc = count_reloc(p);

      if (num_reloc == 0) {

        address = maybe_evaluate(p);
        page = gp_processor_check_page(state.device.class, address);

        state.org += gp_processor_set_page(state.device.class,
                                           state.processor_info->num_pages,
                                           page,
                                           state.i_memory,
                                           state.org,
                                           use_wreg);
      } else if (num_reloc != 1) {
        gperror(GPE_ILLEGAL_LABEL, NULL);
      } else if (state.device.class == PROC_CLASS_PIC16) {
        reloc_evaluate(p, RELOCT_PAGESEL_WREG);
        emit(0);
        emit(0);
      } else {
        if ((use_wreg == 0) &&
            (state.processor_info->num_pages == 2)) {
          reloc_evaluate(p, RELOCT_PAGESEL_BITS);
          emit(0);
        }
        else if ((state.processor_info->num_pages == 2) ||
            (state.processor_info->num_pages == 4)) {
          reloc_evaluate(p, reloc_type);
          emit(0);
          emit(0);
        }
      }
    }

  }

  return r;
}

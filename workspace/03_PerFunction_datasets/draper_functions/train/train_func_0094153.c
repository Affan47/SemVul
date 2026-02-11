symtable_add_sym_sig(
  symtable* symtab,
  vsignal*  sig,
  int       msb,
  int       lsb
) { PROFILE(SYMTABLE_ADD_SYM_SIG);

  sym_sig* new_ss;


  new_ss       = (sym_sig*)malloc_safe( sizeof( sym_sig ) );
  new_ss->sig  = sig;
  new_ss->msb  = msb;
  new_ss->lsb  = lsb;
  new_ss->next = NULL;


  if( symtab->sig_head == NULL ) {
    symtab->sig_head = symtab->sig_tail = new_ss;
  } else {
    symtab->sig_tail->next = new_ss;
    symtab->sig_tail       = new_ss;
  }

  PROFILE_END;

}

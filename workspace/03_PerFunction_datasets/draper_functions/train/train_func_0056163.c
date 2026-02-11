take_to_addrbooks_frontend(char **new_entries, char *nick, char *fullname,
			   char *addr, char *fcc, char *comment, int cmdline,
			   TA_STATE_S **tas, char *cmd)
{
    jmp_buf save_jmp_buf;
    int    *save_nesting_level;

    dprint((5, "-- take_to_addrbooks_frontend --\n"));

    if(ps_global->remote_abook_validity > 0 &&
       adrbk_check_and_fix_all(ab_nesting_level == 0, 0, 0))
      ps_global->mangled_footer = 1;

    save_nesting_level = cpyint(ab_nesting_level);
    memcpy(save_jmp_buf, addrbook_changed_unexpectedly, sizeof(jmp_buf));
    if(setjmp(addrbook_changed_unexpectedly)){
	q_status_message(SM_ORDER, 5, 10, _("Resetting address book..."));
	dprint((1,
	    "RESETTING address book... take_to_addrbooks_frontend!\n"));
	addrbook_reset();
	ab_nesting_level = *save_nesting_level;
    }

    ab_nesting_level++;
    take_to_addrbooks(new_entries, nick, fullname, addr, fcc, comment, cmdline,
		      tas, cmd);
    memcpy(addrbook_changed_unexpectedly, save_jmp_buf, sizeof(jmp_buf));
    ab_nesting_level--;
    if(save_nesting_level)
      fs_give((void **)&save_nesting_level);
}

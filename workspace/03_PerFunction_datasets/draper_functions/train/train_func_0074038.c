pop_file_context(pCPP_ struct lexer_state *ls)
{
#ifdef AUDIT
	if (ls_depth <= 0) ouch(aCPP_ "prepare to meet thy creator");
#endif
	close_input(ls);
	restore_lexer_state(ls, &(ls_stack[-- ls_depth].ls));
	if (protect_detect.macro) freemem(protect_detect.macro);
	protect_detect = protect_detect_stack[ls_depth];
	if (current_filename) freemem(current_filename);
	current_filename = ls_stack[ls_depth].name;
	current_long_filename = ls_stack[ls_depth].long_name;
	current_incdir = ls_stack[ls_depth].incdir;
	if (ls_depth == 0) {
		freemem(ls_stack);
		freemem(protect_detect_stack);
	}
}

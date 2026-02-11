complete_step(String *retval)
{
    int last_insn;
    if (_insn_pos < 0 || _insn_pos >= _insns.size())
	last_insn = -1;
    else {
	last_insn = _insns[_insn_pos];
	if (last_insn == INSN_GOTO && _args[_insn_pos] < 0)
	    last_insn = _args[_insn_pos];
    }

#if CLICK_USERLEVEL
    if (last_insn == insn_end && _type == type_signal)
	for (int i = 0; i < _signos.size(); i++)
	    master()->add_signal_handler(_signos[i], router(), name() + ".run");
#endif

    if (retval) {
	int x;
	*retval = String();
	if (last_insn == INSN_RETURN || last_insn == insn_returnq) {
	    x = find_variable(String::make_stable("_", 1), false);
	    if (x < _vars.size())
		*retval = _vars[x + 1];
	} else if (last_insn == insn_end && _type == type_push)
	    *retval = String::make_stable("0", 1);
    }

    if (last_insn == insn_error || last_insn == insn_errorq)
	return -1;
    else if (last_insn == insn_stop)
	return 1;
    else
	return 0;
}

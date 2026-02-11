set_ticsCmd()
{
	if (_nword != 3) {
		demonstrate_command_usage();
		NUMBER_WORDS_ERROR;
		return false;
	}
	if (!strcmp(_word[2], "in")) {
		PUT_VAR("..tic_direction..", 1.0);
	} else if (!strcmp(_word[2], "out")) {
		PUT_VAR("..tic_direction..", 0.0);
	} else {
		demonstrate_command_usage();
		err("Third word must be \"in\" or \"out\".");
		return false;
	}
	return true;
}

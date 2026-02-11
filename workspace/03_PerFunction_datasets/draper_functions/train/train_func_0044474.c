rpnfunctionCmd()
{
	if (_nword < 3) {
		demonstrate_command_usage();
		err("Need some action for this rpn function");
		return false;
	}
	rpn_create_function(_word[1], &_word[2], _nword - 2);
	return true;
}

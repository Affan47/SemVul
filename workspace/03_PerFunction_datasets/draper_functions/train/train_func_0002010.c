register_source()
{
	GET_STORAGE(_command[_num_command].filename, char,
		    1 + strlen(_cmdFILE.back().get_name()));
	strcpy(_command[_num_command].filename, _cmdFILE.back().get_name());
	_command[_num_command].fileline = _cmdFILE.back().get_line() + 1;
}

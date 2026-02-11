what_file()
{
	if (_cmdFILE.size() == 0)
		return NULL;
	if (block_level() > 0) {
		if (_cmd_being_done < 1) {
			return NULL;
		} else {
			return _command[_cmd_being_done_code[_cmd_being_done - 1]].filename;
		}
	} else {
		return _cmdFILE.back().get_name();
	}
}

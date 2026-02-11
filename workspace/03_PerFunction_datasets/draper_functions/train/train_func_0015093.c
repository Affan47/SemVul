heal_columnsCmd()
{
	if (_nword != 2) {
		NUMBER_WORDS_ERROR;
		demonstrate_command_usage();
		return false;
	}
	if (_colX.size() > 0)
		heal_col(_colX.begin(), _colX.size());
	if (_colY.size() > 0)
		heal_col(_colY.begin(), _colY.size());
	if (_colU.size() > 0)
		heal_col(_colU.begin(), _colU.size());
	if (_colV.size() > 0)
		heal_col(_colV.begin(), _colV.size());
	if (_colZ.size() > 0)
		heal_col(_colZ.begin(), _colZ.size());
	if (_colWEIGHT.size() > 0)
		heal_col(_colWEIGHT.begin(), _colWEIGHT.size());
	return true;
}

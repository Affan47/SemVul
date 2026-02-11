type2_command(int cmd, const unsigned char *data, int *left)
{
    if (_start_of_line) {
	_sa << _indent;
	_start_of_line = false;
    } else
	_sa << ' ';

    if (cmd >= 0 && cmd <= Cs::cLastCommand)
	_sa << Cs::command_names[cmd];
    else
	_sa << "UNKNOWN_12_" << (cmd - 32);

    switch (cmd) {
      case Cs::cHstem: case Cs::cHstemhm: case Cs::cVstem: case Cs::cVstemhm:
      case Cs::cHintmask: case Cs::cCntrmask:
	CharstringInterp::type2_command(cmd, data, left);
	break;
    }

    if (_one_command_per_line) {
	_sa << '\n';
	_start_of_line = true;
    }

    return true;
}

type1_command(int cmd)
{
    switch (cmd) {
    case Cs::cReturn:
	_returned = true;
	return false;
    default:
	clear();
	return true;
    }
}

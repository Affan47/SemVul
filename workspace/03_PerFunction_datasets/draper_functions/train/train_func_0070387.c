INSmode(on)
bool	on;
{
	if (on != IN_INSmode) {
		putpad(on? IM : EI, 1);
		IN_INSmode = on;
	}
}

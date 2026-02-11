pin_flag(int pinned)
{
	if (pinned > 0)
		return " P";
	else if (pinned < 0)
		return " p";
	else
		return "";
}

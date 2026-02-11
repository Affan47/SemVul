Select()
{
	if (Action)
	{
		Action(data);
		return true;
	}

	return false;
}

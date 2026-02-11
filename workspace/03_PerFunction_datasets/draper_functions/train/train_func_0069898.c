loginResponse(int n, string msg)
{
	if ((n / 100) != 2)
	{
		error(msg);
		return;
	}

	authenticated();
}

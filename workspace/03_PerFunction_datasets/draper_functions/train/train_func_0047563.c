is_soper(myuser_t *myuser)
{
	if (!myuser)
		return false;

	if (myuser->soper)
		return true;

	return false;
}

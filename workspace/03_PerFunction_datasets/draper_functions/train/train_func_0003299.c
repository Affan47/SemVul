xs_error(char *reply)
{
	if (IS_ERR(reply))
		return PTR_ERR(reply);
	kfree(reply);
	return 0;
}

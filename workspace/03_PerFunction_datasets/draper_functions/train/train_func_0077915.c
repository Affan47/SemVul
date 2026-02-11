get_flag(const char *name)
{
	for (unsigned int i = 0; i < num_flags; i++)
		if (flag[i].name == name)
			return flag[i].value;
	return false;
}

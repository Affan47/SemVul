is_special(const char *name)
{
    if(name[0] == '.' &&
       (name[1] == '\0' || (name[1] == '.' && name[2] == '\0')))
	return 1;

    return 0;
}

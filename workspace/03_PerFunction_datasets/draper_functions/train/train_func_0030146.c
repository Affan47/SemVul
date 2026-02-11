integer_write(output::pointer fp, const char *name, long this_thing, int show)
{
    if (this_thing == INTEGER_NOT_SET && !show)
	return;
    if (name)
	fp->fprintf("%s = ", name);
    if (name && !strcmp(name, "umask"))
	fp->fprintf("0%lo", this_thing & 07777);
    else
    {
	if (this_thing == MAGIC_ZERO)
    	    fp->fputs("ZERO");
	else
    	    fp->fprintf("%ld", this_thing);
    }
    if (name)
	fp->fputs(";\n");
}

save_keystring(struct uih_context *uih, const char *name)
{
    if (!first)
	myputc(' ');
    else
	first = 0;
    myputc('\'');
    myputs(name);
}

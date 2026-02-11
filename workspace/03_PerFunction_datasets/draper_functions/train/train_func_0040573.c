user_deco_define(char *name)
{
	struct u_deco *d;
	int l;

	l = strlen(name);
	for (d = user_deco; d != 0; d = d->next) {
		if (strncmp(d->text, name, l) == 0
		 && d->text[l] == ' ')
			return deco_build(d->text);
	}
	return 128;
}

ui_getextension(const char *ch)
{
    int i = 0;
    while (ch[i]) {
	if (ch[i] == '*')
	    return (ch + i + 1);
	i++;
    }
    return ch + i;
}

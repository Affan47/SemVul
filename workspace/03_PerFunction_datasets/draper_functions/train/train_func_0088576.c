script_word (const zchar *s)
{
    int width;
    int i;

    if (*s == ZC_INDENT && script_width != 0)
	script_char (*s++);

    for (i = 0, width = 0; s[i] != 0; i++)

	if (s[i] == ZC_NEW_STYLE || s[i] == ZC_NEW_FONT)
	    i++;
	else if (s[i] == ZC_GAP)
	    width += 3;
	else if (s[i] == ZC_INDENT)
	    width += 2;
	else
	    width += 1;

    if (f_setup.script_cols != 0 && script_width + width > f_setup.script_cols) {

	if (*s == ' ' || *s == ZC_INDENT || *s == ZC_GAP)
	    s++;

	script_new_line ();

    }

    for (i = 0; s[i] != 0; i++)

	if (s[i] == ZC_NEW_FONT || s[i] == ZC_NEW_STYLE)
	    i++;
	else
	    script_char (s[i]);

}

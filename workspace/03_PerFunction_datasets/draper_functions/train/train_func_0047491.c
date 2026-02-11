script_write_input (const zchar *buf, zchar key)
{
    int width;
    int i;

    for (i = 0, width = 0; buf[i] != 0; i++)
	width++;

    if (f_setup.script_cols != 0 && script_width + width > f_setup.script_cols)
	script_new_line ();

    for (i = 0; buf[i] != 0; i++)
	script_char (buf[i]);

    if (key == ZC_RETURN)
	script_new_line ();

}

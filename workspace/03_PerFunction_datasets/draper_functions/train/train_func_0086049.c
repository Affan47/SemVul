prt_dsc_ints(comment, count, ints)
    char	*comment;
    int		count;
    int		*ints;
{
    int		i;

    vim_snprintf((char *)prt_line_buffer, sizeof(prt_line_buffer),
							  "%%%%%s:", comment);
    prt_write_file(prt_line_buffer);

    for (i = 0; i < count; i++)
    {
	sprintf((char *)prt_line_buffer, " %d", ints[i]);
	prt_write_file(prt_line_buffer);
    }

    prt_write_string("\n");
}

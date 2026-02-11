parse_color_name()
{
    char *string;
    long color = -2;


    if (almost_equals(c_token,"rgb$color") && almost_equals(c_token-1,"back$ground"))
	c_token++;
    if ((string = try_to_get_string())) {
	color = lookup_table_nth(pm3d_color_names_tbl, string);
	if (color >= 0)
	    color = pm3d_color_names_tbl[color].value;
	else
	    sscanf(string,"#%lx",&color);
	free(string);
	if (color == -2)
	    int_error(c_token, "unrecognized color name and not a string \"#AARRGGBB\"");
    } else {
	color = int_expression();
    }

    return (unsigned int)(color);
}

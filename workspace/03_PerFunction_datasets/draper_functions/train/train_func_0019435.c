has_colors(void)
{
    T((T_CALLED("has_colors()")));
    returnCode((VALID_NUMERIC(max_colors) && VALID_NUMERIC(max_pairs)
		&& (((set_foreground != NULL)
		     && (set_background != NULL))
		    || ((set_a_foreground != NULL)
			&& (set_a_background != NULL))
		    || set_color_pair)) ? TRUE : FALSE);
}

unset_clip()
{
    if (END_OF_COMMAND) {

	clip_points = FALSE;
	clip_lines1 = FALSE;
	clip_lines2 = FALSE;
    } else if (almost_equals(c_token, "p$oints"))
	clip_points = FALSE;
    else if (almost_equals(c_token, "o$ne"))
	clip_lines1 = FALSE;
    else if (almost_equals(c_token, "t$wo"))
	clip_lines2 = FALSE;
    else
	int_error(c_token, "expecting 'points', 'one', or 'two'");
    c_token++;
}

show_zeroaxis(AXIS_INDEX axis)
{
    SHOW_ALL_NL;

    if (axis_array[axis].zeroaxis.l_type > LT_NODRAW) {
	fprintf(stderr, "\t%szeroaxis is drawn with", axis_defaults[axis].name);
	save_linetype(stderr, &(axis_array[axis].zeroaxis), FALSE);
	fputc('\n',stderr);
    } else
	fprintf(stderr, "\t%szeroaxis is OFF\n", axis_defaults[axis].name);

    if ((axis / SECOND_AXES) == 0) {


	show_zeroaxis(axis + SECOND_AXES);
    }
}

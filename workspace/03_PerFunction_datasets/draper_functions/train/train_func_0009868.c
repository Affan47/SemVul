show_format()
{
    SHOW_ALL_NL;

    fprintf(stderr, "\ttic format is:\n");
#define SHOW_FORMAT(_axis)						\
    fprintf(stderr, "\t  %s-axis: \"%s\"\n", axis_defaults[_axis].name,	\
	    conv_text(axis_array[_axis].formatstring));
    SHOW_FORMAT(FIRST_X_AXIS );
    SHOW_FORMAT(FIRST_Y_AXIS );
    SHOW_FORMAT(SECOND_X_AXIS);
    SHOW_FORMAT(SECOND_Y_AXIS);
    SHOW_FORMAT(FIRST_Z_AXIS );
    SHOW_FORMAT(COLOR_AXIS);
    SHOW_FORMAT(POLAR_AXIS);
#undef SHOW_FORMAT
}

show_logscale()
{
    int count = 0;

    SHOW_ALL_NL;

#define SHOW_LOG(axis)							\
    {									\
	if (axis_array[axis].log) 					\
	    fprintf(stderr, "%s %s (base %g)",				\
		    !count++ ? "\tlogscaling" : " and",			\
		    axis_defaults[axis].name,axis_array[axis].base);	\
    }
    SHOW_LOG(FIRST_X_AXIS );
    SHOW_LOG(FIRST_Y_AXIS );
    SHOW_LOG(FIRST_Z_AXIS );
    SHOW_LOG(SECOND_X_AXIS);
    SHOW_LOG(SECOND_Y_AXIS);
    SHOW_LOG(COLOR_AXIS );
    SHOW_LOG(POLAR_AXIS );
#undef SHOW_LOG

    if (count == 0)
	fputs("\tno logscaling\n", stderr);
    else if (count == 1)
	fputs(" only\n", stderr);
    else
	putc('\n', stderr);
}

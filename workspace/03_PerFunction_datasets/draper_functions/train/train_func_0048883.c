init(void)
{
	int ctl;

	filltable("CWORD");
	syntax[0] = "CEOF";
	syntax[1] = "CIGN";
	for (ctl = CTL_FIRST; ctl <= CTL_LAST; ctl++ )
		syntax[130 + ctl] = "CCTL";
}

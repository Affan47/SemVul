Xattrputs(s, isstandout)
CONST char *s;
int isstandout;
{
	if (!s || !*s) return;

	if (isstandout) Xputterm(T_STANDOUT);
	XXcputs(s);
	if (isstandout) Xputterm(END_STANDOUT);
}

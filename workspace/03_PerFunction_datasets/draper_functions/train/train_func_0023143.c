push_primary(struct i_primary *pri)
{
exp_pnt++;
if(exp_pnt==(exp_root+EXP_ROOT_SIZE))
	{
	mesg("\n** Error: overflow of %d element expression stack\n", EXP_ROOT_SIZE);
	zzerrors+=zzLexErrCount;
	warn("** %d error%s detected, exiting.\n\n",zzerrors,(zzerrors>1)?"s were":" was");
	exit(255);
	}
*exp_pnt=(void *)pri;
}

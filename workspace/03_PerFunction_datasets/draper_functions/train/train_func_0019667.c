newlevel()
{
    if (*(unsigned *) chartop != MARKER)
	heapcorrupterror();
    if (level >= MAXLEVEL)
	limiterror("compound statements nested too deeply (126 levels)");
    else
	++level;
}

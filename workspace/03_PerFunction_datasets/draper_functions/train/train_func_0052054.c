doPushd(newdir)
	char	*newdir;
{
	UpdModLine = YES;
	if (*newdir == '\0') {
		if (list_next(DirStack) == NULL)
			complain("pushd: no other directory.");
		newdir = dir_name(list_next(DirStack));
		if (Dchdir(newdir) == -1)
		{
			s_mess("pushd: cannot change back into %s.", newdir);
			return;
		}
		list_data(list_next(DirStack)) = list_data(DirStack);
		list_data(DirStack) = (UnivPtr) newdir;
	} else {
		if (Dchdir(newdir) == -1)
		{
			s_mess("pushd: cannot change into %s.", newdir);
			return;
		}
		(void) list_push(&DirStack, (UnivPtr)NULL);
		setCWD(newdir);
	}
	prDIRS();
}

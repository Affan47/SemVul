Arch_Touch(GNode *gn)
{
	struct arfile	*ar;

	ar = ArchFindMember(Var_Value(ARCHIVE, gn),
	    Var_Value(TARGET, gn), "r+");

	if (ar != NULL) {
		ArchArchiveTouch(ar, (int64_t)now);
		ArchArchiveClose(ar);
	}
}

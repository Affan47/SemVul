hashcd(void)
{
	struct tblentry **pp;
	struct tblentry *cmdp;

	for (pp = cmdtable ; pp < &cmdtable[CMDTABLESIZE] ; pp++) {
		for (cmdp = *pp ; cmdp ; cmdp = cmdp->next) {
			if (cmdp->cmdtype == CMDNORMAL || (
				cmdp->cmdtype == CMDBUILTIN &&
				!(cmdp->param.cmd->flags & BUILTIN_REGULAR) &&
				builtinloc > 0
			))
				cmdp->rehash = 1;
		}
	}
}

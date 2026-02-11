hashcd(void)
{
	struct tblentry **pp;
	struct tblentry *cmdp;

	for (pp = cmdtable; pp < &cmdtable[CMDTABLESIZE]; pp++) {
		for (cmdp = *pp; cmdp; cmdp = cmdp->next) {
			if (cmdp->cmdtype == CMDNORMAL
			 || (cmdp->cmdtype == CMDBUILTIN
			     && !IS_BUILTIN_REGULAR(cmdp->param.cmd)
			     && builtinloc > 0)
			) {
				cmdp->rehash = 1;
			}
		}
	}
}

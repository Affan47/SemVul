checkGuard(Exnode_t * gp, char *src, int line)
{
    gp = exnoncast(gp);
    if (gp && exisAssign(gp)) {
	if (src) {
	    setErrorFileLine (src, line);
	}
	error(ERROR_WARNING, "assignment used as bool in guard");
    }
}

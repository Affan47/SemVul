rename_file (const char *from, const char *to)
{
    TRACE (TRACE_FUNCTION, "rename(%s,%s)", from, to);

    if (noexec)
	return;

    if (rename (from, to) < 0)
	error (1, errno, "cannot rename file %s to %s", from, to);
}

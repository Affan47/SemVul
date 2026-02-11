checkLogdir()
{
	return !inPaths(sLogdir, "/dev:/proc:/sys");
}

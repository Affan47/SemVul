removeDir(string const& dir)
{
	if (!rmdir(dir.c_str())) {
		gOut.vrb("Removed directory '" + dir + "'\n");
		removeParentDir(dir);
	}
	else if (errno != ENOTEMPTY)
		gOut.vrb("rmdir(" + dir + ")", errno);
}

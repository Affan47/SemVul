InitNGTable(void)
{
    if (!ReadDBFile()) return false;


    NGTableUpdated = false;
    if (!SMopenmode)

	return true;
    return ReadActiveFile();
}

WriteToLog(int n)
{
	if (g_strmLog.fail())
	{
		std::cout << "Error opening log file.";
		return false;
	}
	g_strmLog << n;
	g_strmLog.flush();
	return true;
}

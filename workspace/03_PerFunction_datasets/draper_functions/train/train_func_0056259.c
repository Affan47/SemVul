WriteToLog(std::string str1, int i1, std::string str2, int i2)
{
	if (g_strmLog.fail())
	{
		std::cout << "Error opening log file.";
		return false;
	}
	g_strmLog << str1;
	if (i1 > -1)
		g_strmLog << "[" << i1 << "]";
	g_strmLog << str2;
	if (i2 > -1)
		g_strmLog << "[" << i2 << "]";
	g_strmLog.flush();
	return true;
}

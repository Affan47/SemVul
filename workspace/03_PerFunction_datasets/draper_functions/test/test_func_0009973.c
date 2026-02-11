GetDataPath( string FileName )
{

	string path = GetConfigPath(FileName);

	FILE *fp;
	if( (fp = fopen(path.c_str(), "r")) )
	{
		fclose(fp);
		return path;
	}
	path = m_DataDirPath;
	path += FileName;
	return path;
}

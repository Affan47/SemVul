checkDir( string &rootDir )
{
    if( !isDirectory( rootDir.c_str() ))
    {
	cerr << autosprintf(_("directory %s does not exist.\n"),
		rootDir.c_str());
	return false;
    }
    if(rootDir[ rootDir.length()-1 ] != '/')
	rootDir.append("/");

    return true;
}

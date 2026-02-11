openDir(const char *plaintextPath)
{
    string cyName = rootDir + naming->encodePath( plaintextPath );


    DIR *dir = ::opendir( cyName.c_str() );
    if(dir == NULL)
    {
	rDebug("opendir error %s", strerror(errno));
	return DirTraverse( shared_ptr<DIR>(), 0, shared_ptr<NameIO>() );
    } else
    {
        shared_ptr<DIR> dp( dir, DirDeleter() );

	uint64_t iv = 0;


	try
	{
	    if( naming->getChainedNameIV() )
		naming->encodePath( plaintextPath, &iv );
	} catch( rlog::Error &err )
	{
	    rError("encode err: %s", err.message());
	    err.log( _RLWarningChannel );
	}
	return DirTraverse( dp, iv, naming );
    }
}

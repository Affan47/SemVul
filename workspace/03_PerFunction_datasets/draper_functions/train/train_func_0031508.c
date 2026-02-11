traverseDirs(const shared_ptr<EncFS_Root> &rootInfo,
	string volumeDir, string destDir)
{
    if(!endsWith(volumeDir, '/'))
	volumeDir.append("/");
    if(!endsWith(destDir, '/'))
	destDir.append("/");


    {
        struct stat st;
        shared_ptr<FileNode> dirNode =
            rootInfo->root->lookupNode( volumeDir.c_str(), "encfsctl" );
        if(dirNode->getAttr(&st))
            return EXIT_FAILURE;

        mkdir(destDir.c_str(), st.st_mode);
    }


    DirTraverse dt = rootInfo->root->openDir(volumeDir.c_str());
    if(dt.valid())
    {
        for(string name = dt.nextPlaintextName(); !name.empty();
            name = dt.nextPlaintextName())
        {

            if(name != "." && name != "..")
            {
                string plainPath = volumeDir + name;
                string cpath = rootInfo->root->cipherPath(plainPath.c_str());
                string destName = destDir + name;

                int r = EXIT_SUCCESS;
                struct stat stBuf;
                if( !lstat( cpath.c_str(), &stBuf ))
                {
                    if( S_ISDIR( stBuf.st_mode ) )
                    {
                        traverseDirs(rootInfo, (plainPath + '/').c_str(),
                                destName + '/');
                    } else if( S_ISLNK( stBuf.st_mode ))
                    {
                        r = copyLink( stBuf, rootInfo, cpath, destName );
                    } else
                    {
                        r = copyContents(rootInfo, plainPath.c_str(),
                                destName.c_str());
                    }
                } else
                {
                    r = EXIT_FAILURE;
                }

                if(r != EXIT_SUCCESS)
                    return r;
            }
        }
    }
    return EXIT_SUCCESS;
}

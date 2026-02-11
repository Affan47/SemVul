copyContents(const shared_ptr<EncFS_Root> &rootInfo,
                        const char* encfsName, const char* targetName)
{
    shared_ptr<FileNode> node =
	rootInfo->root->lookupNode( encfsName, "encfsctl" );

    if(!node)
    {
        cerr << "unable to open " << encfsName << "\n";
        return EXIT_FAILURE;
    } else
    {
        struct stat st;

        if(node->getAttr(&st) != 0)
            return EXIT_FAILURE;

        if((st.st_mode & S_IFLNK) == S_IFLNK)
        {
            string d = rootInfo->root->cipherPath(encfsName);
            char linkContents[PATH_MAX+2];

            if(readlink (d.c_str(), linkContents, PATH_MAX + 1) <= 0)
            {
                cerr << "unable to read link " << encfsName << "\n";
                return EXIT_FAILURE;
            }
            symlink(rootInfo->root->plainPath(linkContents).c_str(),
		    targetName);
        } else
        {
            int outfd = creat(targetName, st.st_mode);

	    WriteOutput output(outfd);
	    processContents( rootInfo, encfsName, output );
        }
    }
    return EXIT_SUCCESS;
}

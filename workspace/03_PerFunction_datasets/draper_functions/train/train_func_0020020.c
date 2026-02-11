remoteStatus(Client * client,
               const char * path,
               const bool descend,
               StatusEntries & entries,
               Context * )
  {
    Revision rev(Revision::HEAD);
    DirEntries dirEntries = client->list(path, rev, descend);
    DirEntries::const_iterator it;
    svn_revnum_t revnum = 0;

    for (it = dirEntries.begin(); it != dirEntries.end(); it++)
    {
      const DirEntry & dirEntry = *it;

      entries.push_back(dirEntryToStatus(path, dirEntry));
    }

    if (dirEntries.size() > 0)
      revnum = dirEntries[0].createdRev();


    return revnum;
  }

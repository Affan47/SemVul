xfs_release( XfsCookie *fc )
{
    D2(bug( "release():\n"
         "  fc = %08lx\n"
         "    fs    = %08lx\n"
         "    dev   = %04x\n"
         "    aux   = %04x\n"
         "    index = %08lx\n"
         "      parent   = %08lx\n"
         "      name     = \"%s\"\n"
         "      usecnt   = %d\n"
         "      childcnt = %d\n",
         (long)fc,
         (long)fc->xfs,
         (int)fc->dev,
         (int)fc->aux,
         (long)fc->index,
         (long)fc->index->parent,
           fc->index->name,
           fc->index->refCount,
           fc->index->childCount ));

    if ( !fc->index->refCount )
    {
        D(bug( "HOSTFS: fs_release: RELEASE OF UNUSED FILECOOKIE!" ));
        return TOS_EACCDN;
    }
    fc->index->refCount--;
    xfs_freefs( fc->index );

    return TOS_E_OK;
}

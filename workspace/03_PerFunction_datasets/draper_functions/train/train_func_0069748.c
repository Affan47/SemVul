slCompleted( const KUrl& url )
{
    kDebug(250) << "SlotCompleted hit for " << url.prettyUrl();
    K3FileTreeViewItem *currParent = findTVIByUrl( url );
    if( ! currParent ) return;

    kDebug(250) << "current parent " << currParent << " is already listed: "
                 << currParent->alreadyListed() << endl;

    emit( populateFinished(currParent));
    emit( directoryChildCount(currParent, currParent->childCount()));


    currParent->setListed(true);

    kDebug(250) << "recurseChildren: " << m_recurseChildren;
    kDebug(250) << "isLocalFile: " << m_startURL.isLocalFile();
    kDebug(250) << "dirOnlyMode: " << dirOnlyMode();


    if( m_recurseChildren && (!m_startURL.isLocalFile() || ! dirOnlyMode()) )
    {
        bool wantRecurseUrl = false;

        for ( KUrl::List::Iterator it = m_openChildrenURLs.begin();
              it != m_openChildrenURLs.end(); ++it )
        {

          if( (*it).equals( url, KUrl::CompareWithoutTrailingSlash ) )
                wantRecurseUrl = true;
        }

        K3FileTreeViewItem    *nextChild = 0;
        kDebug(250) << "Recursing " << url.prettyUrl() << "? " << wantRecurseUrl;

        if( wantRecurseUrl && currParent )
        {


            nextChild = static_cast<K3FileTreeViewItem*>
                        (static_cast<Q3ListViewItem*>(currParent)->firstChild());

            if( ! nextChild )
            {

                kDebug( 250 ) << "No children to recuse";
            }


            m_openChildrenURLs.removeAll(url);
        }

        if( nextChild )
        {


            while( nextChild )
            {
                if( nextChild->isDir() && ! nextChild->alreadyListed())
                {
                    const KFileItem kfi = nextChild->fileItem();
                    if( !kfi.isNull() && kfi.isReadable())
                    {
                        KUrl recurseUrl = kfi.url();
                        kDebug(250) << "Starting to recurse NOW " << recurseUrl.prettyUrl();
                        openUrl( recurseUrl, KDirLister::Keep );
                    }
                }
                nextChild = static_cast<K3FileTreeViewItem*>(nextChild->nextSibling());

            }
        }
    }
    else
    {
        kDebug(250) << "skipping to recurse in complete-slot";
    }
}

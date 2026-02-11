populateMimeData( QMimeData* mimeData ) const
{
    KBookmark::List bookmarkList;
    bookmarkList.append( *this );
    bookmarkList.populateMimeData( mimeData );
}

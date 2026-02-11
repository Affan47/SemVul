setImageUrl( const KUrl &imageUrl )
{
    DEBUG_BLOCK
    debug() << imageUrl;
    m_imageUrl = imageUrl;

    if( imageUrl.isLocalFile() )
    {
        m_image = QImage( imageUrl.path() );
        return;
    }

    debug() << "Image is remote, handled by podcastImageFetcher.";
}

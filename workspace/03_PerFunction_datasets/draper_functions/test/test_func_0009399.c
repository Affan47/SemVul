setOpenPixmap( const QPixmap& pix )
{
    m_openRootIcon = pix;

    if( root()->isOpen())
    {
        root()->setPixmap( 0, pix );
    }
}

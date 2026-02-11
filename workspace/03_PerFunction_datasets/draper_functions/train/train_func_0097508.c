display()
{
    CoverFoundItem *item = static_cast< CoverFoundItem* >( m_view->currentItem() );
    const bool success = item->hasBigPix() ? true : fetchBigPix();
    if( !success )
        return;

    const QImage &image = item->hasBigPix() ? item->bigPix() : item->thumb();
    QWeakPointer<CoverViewDialog> dlg = new CoverViewDialog( image, this );
    dlg.data()->show();
    dlg.data()->raise();
    dlg.data()->activateWindow();
}

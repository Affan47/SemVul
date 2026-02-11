saveBackground(const QString &destination)
{
    KUrl back = part->backgroundURL();
    if (back.isEmpty())
        return;

    KIO::MetaData metaData;
    metaData["referrer"] = part->referrer();
    KHTMLPopupGUIClient::saveURL( part->widget(), back, KUrl( destination ), metaData );
}

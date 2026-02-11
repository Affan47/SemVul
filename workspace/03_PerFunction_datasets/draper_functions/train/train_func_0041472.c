slotBlockImage()
{
    bool ok = false;

    QString url = KInputDialog::getText( i18n("Add URL to Filter"),
                                         i18n("Enter the URL:"),
                                         d->m_imageURL.url(),
                                         &ok);
    if ( ok ) {
        KHTMLGlobal::defaultHTMLSettings()->addAdFilter( url );
        d->m_khtml->reparseConfiguration();
    }
}

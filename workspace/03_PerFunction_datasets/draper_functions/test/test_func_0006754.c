slotBlockHost()
{
    QString name=d->m_imageURL.protocol()+"://"+d->m_imageURL.host()+"/*";
    KHTMLGlobal::defaultHTMLSettings()->addAdFilter( name );
    d->m_khtml->reparseConfiguration();
}

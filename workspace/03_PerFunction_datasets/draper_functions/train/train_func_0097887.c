setFileNameReadOnly( bool ro )
{
    foreach(KPropertiesDialogPlugin *it, d->m_pageList) {
        KFilePropsPlugin* plugin = dynamic_cast<KFilePropsPlugin*>(it);
        if ( plugin ) {
            plugin->setFileNameReadOnly( ro );
            break;
        }
    }
}

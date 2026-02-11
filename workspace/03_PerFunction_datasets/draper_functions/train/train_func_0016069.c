registerProvider( const ProviderPtr &provider )
{
    QString id = provider->id();
    bool enabled = false;
    if( m_config->providerKnown( id ) )
        enabled = m_config->providerEnabled( id, false );
    else
    {
        switch( provider->defaultPreference() )
        {
            case Provider::Never:
            case Provider::NoByDefault:
                enabled = false;
                break;
            case Provider::Ask:
            {
                QString text = i18nc( "%1 is collection name", "%1 has an ability to "
                    "synchronize track meta-data such as play count or rating "
                    "with other collections. Do you want to keep %1 synchronized?\n\n"
                    "You can always change the decision in Amarok configuration.",
                    provider->prettyName() );
                enabled = KMessageBox::questionYesNo( The::mainWindow(), text ) == KMessageBox::Yes;
                break;
            }
            case Provider::YesByDefault:
                enabled = true;
                break;
        }
    }


    if( provider->defaultPreference() != Provider::Never )
    {
        m_config->updateProvider( id, provider->prettyName(), provider->icon(), true, enabled );
        m_config->save();
    }
    m_providers.append( provider );
    connect( provider.data(), SIGNAL(updated()), SLOT(slotProviderUpdated()) );
    if( enabled )
        delayedStartSynchronization();
}

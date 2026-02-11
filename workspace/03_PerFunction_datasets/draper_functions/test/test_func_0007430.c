slotSetActionText( const char * name, const QString& text )
{

    ActionNumberMap::ConstIterator it = s_actionNumberMap->constFind( name );
    if ( it != s_actionNumberMap->constEnd() )
    {
        d->m_actionText[ it.value() ] = text;
    }
    else
        kWarning() << "BrowserExtension::slotSetActionText unknown action " << name;
}

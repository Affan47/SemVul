setPluginInfos( const QMap<QString, KPluginInfo*> &
        plugininfos )
{
    for( QMap<QString, KPluginInfo*>::ConstIterator it = plugininfos.begin();
            it != plugininfos.end(); ++it )
    {
        d->plugininfolist.append( it.value() );
    }
}

writeConfig( KConfig *config )
{
    if ( mReference != mLoadedValue )
    {
        KConfigGroup cg(config, mGroup );
        if ((mDefault == mReference) && !cg.hasDefault( mKey))
            cg.revertToDefault( mKey );
        else
            cg.writeEntry<QStringList>( mKey, mReference.toStringList() );
    }
}

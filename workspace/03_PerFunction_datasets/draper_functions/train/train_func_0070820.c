writeConfig( KConfig *config )
{
  if ( mReference != mLoadedValue )
  {
    KConfigGroup cg(config, mGroup );
    if ((mDefault == mReference) && !cg.hasDefault( mKey))
      cg.revertToDefault( mKey );
    else {
      QStringList sl = mReference;
      cg.writePathEntry( mKey, sl );
    }
  }
}

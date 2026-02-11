readConfig( KConfig *config )
{
  KConfigGroup cg(config, mGroup );
  if (!cg.hasKey(mKey))
  {
    mReference = mDefault;
  }
  else
  {
    int i = 0;
    mReference = -1;
    QString tmp = cg.readEntry( mKey, QString() ).toLower();
    for(QList<Choice2>::ConstIterator it = mChoices.constBegin();
        it != mChoices.constEnd(); ++it, ++i)
    {
      if ((*it).name.toLower() == tmp)
      {
        mReference = i;
        break;
      }
    }
    if (mReference == -1)
       mReference = cg.readEntry( mKey, mDefault );
  }
  mLoadedValue = mReference;

  readImmutability( cg );
}

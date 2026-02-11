timerExpired()
{
  if( d->mAboutKDE && !d->mAboutKDE->isVisible() )
  {
    delete d->mAboutKDE; d->mAboutKDE = 0;
  }

  if( d->mBugReport && !d->mBugReport->isVisible() )
  {
    delete d->mBugReport; d->mBugReport = 0;
  }

  if ( d->mSwitchApplicationLanguage && !d->mSwitchApplicationLanguage->isVisible() )
  {
    delete d->mSwitchApplicationLanguage; d->mSwitchApplicationLanguage = 0;
  }

  if( d->mAboutApp && !d->mAboutApp->isVisible() )
  {
    delete d->mAboutApp; d->mAboutApp = 0;
  }
}

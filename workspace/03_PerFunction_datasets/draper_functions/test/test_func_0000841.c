isEmpty() const
{
  return
    ( ( d->mIntern && d->mData.isEmpty() ) || ( !d->mIntern && d->mUrl.isEmpty() ) );
}

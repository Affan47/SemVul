setRawData( const QByteArray &rawData, const QString &type )
{
  d->mRawData = rawData;
  d->mType = type;
  d->mData = QImage();
  d->mIntern = true;
}

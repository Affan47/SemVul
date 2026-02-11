operator>>(QDataStream &in, const KCalCore::Attachment::Ptr &a)
{
    if (a)
        in >> a->d->mSize >> a->d->mMimeType >> a->d->mUri >> a->d->mEncodedData >> a->d->mLabel >> a->d->mBinary >> a->d->mLocal >> a->d->mShowInline;
    return in;
}

metaInfo(bool autoget, int what) const
{
    if (!d)
        return KFileMetaInfo();

    if ((isRegularFile() || isDir()) && autoget && !d->m_metaInfo.isValid())
    {
        bool isLocalUrl;
        KUrl url(mostLocalUrl(isLocalUrl));
        d->m_metaInfo = KFileMetaInfo(url.toLocalFile(), mimetype(), (KFileMetaInfo::What)what);
    }
    return d->m_metaInfo;
}

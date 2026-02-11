http_post( const KUrl& url, const QByteArray &postData, JobFlags flags )
{
    QBuffer* device = new QBuffer;
    device->setData(postData);
    device->open(QIODevice::ReadOnly);
    TransferJob* job = http_post(url, device, device->size(), flags);
    device->setParent(job);
    return job;
}

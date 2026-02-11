findByContent( QIODevice* device, int* accuracy )
{
    QByteArray cache;
    return KMimeTypeRepository::self()->findFromContent(device, accuracy, cache);
}

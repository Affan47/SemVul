loadDataHeader()
{

    QFile file(mDataFile);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    KPixmapCacheDataHeader dataHeader;
    if(sizeof dataHeader != file.read(reinterpret_cast<char*>(&dataHeader), sizeof dataHeader)) {
        kDebug(264) << "Unable to read from data file" << mDataFile;
        return false;
    }

    mDataMmapInfo.size = dataHeader.size;
    return true;
}

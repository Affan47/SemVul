slotThumbData(KIO::Job *, const QByteArray &data)
{
    bool save = bSave &&
                currentItem.plugin->property("CacheThumbnail").toBool() &&
                (currentItem.item.url().protocol() != "file" ||
                 !currentItem.item.url().directory( KUrl::AppendTrailingSlash ).startsWith(thumbRoot)) && !sequenceIndex;
    QImage thumb;
#ifdef Q_OS_UNIX
    if (shmaddr)
    {

        QDataStream str(data);
        int width, height;
        quint8 iFormat;
        str >> width >> height >> iFormat;
        QImage::Format format = static_cast<QImage::Format>( iFormat );
        thumb = QImage(shmaddr, width, height, format ).copy();
    }
    else
#endif
        thumb.loadFromData(data);

    if (thumb.isNull()) {
        QDataStream s(data);
        s >> thumb;
    }

    QString tempFileName;
    bool savedCorrectly = false;
    if (save)
    {
        thumb.setText("Thumb::URI", origName);
        thumb.setText("Thumb::MTime", QString::number(tOrig));
        thumb.setText("Thumb::Size", number(currentItem.item.size()));
        thumb.setText("Thumb::Mimetype", currentItem.item.mimetype());
        QString thumbnailerVersion = currentItem.plugin->property("ThumbnailerVersion", QVariant::String).toString();
        QString signature = QString("KDE Thumbnail Generator "+currentItem.plugin->name());
        if (!thumbnailerVersion.isEmpty()) {
            signature.append(" (v"+thumbnailerVersion+')');
        }
        thumb.setText("Software", signature);
        KTemporaryFile temp;
        temp.setPrefix(thumbPath + "kde-tmp-");
        temp.setSuffix(".png");
        temp.setAutoRemove(false);
        if (temp.open())
        {
            tempFileName = temp.fileName();
            savedCorrectly = thumb.save(tempFileName, "PNG");
        }
    }
    if(savedCorrectly)
    {
        Q_ASSERT(!tempFileName.isEmpty());
        KDE::rename(tempFileName, thumbPath + thumbName);
    }
    emitPreview( thumb );
    succeeded = true;
}

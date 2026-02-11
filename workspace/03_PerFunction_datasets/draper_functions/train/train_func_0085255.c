processEOF()
    {
        QBuffer buffer(&array);
        buffer.open(QIODevice::ReadOnly);

        QByteArray qformat = QImageReader::imageFormat(&buffer);
        QImageReader reader(&buffer, qformat);

        if (!reader.canRead()) {
            return Error;
        }

        QSize size = reader.size();
        if (size.isValid()) {
            if (ImageManager::isAcceptableSize(size.width(), size.height()))
                notifyImageInfo(size.width(), size.height());
            else
                return Error;
        }

        if (!reader.read(&image)) {
            return Error;
        }

        if (!size.isValid()) {

            if (ImageManager::isAcceptableSize(image.width(), image.height()))
                notifyImageInfo(image.width(), image.height());
            else
                return Error;
        }

        ImageFormat format;
        if (!imageFormat(image, format)) {
            return Error;
        }
        notifyAppendFrame(image.width(), image.height(), format);

        notifyQImage(1, &image);

        return Done;
    }

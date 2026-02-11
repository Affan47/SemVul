isContentUrl(const QString & url)
{

    if (QFile::exists(url) || url.startsWith("http:/", Qt::CaseInsensitive) ||
        url.startsWith("ftp:/", Qt::CaseInsensitive)) {


        if (isFotowallFile(url) || isPictureFile(url))
            return true;
    }


    return false;
}

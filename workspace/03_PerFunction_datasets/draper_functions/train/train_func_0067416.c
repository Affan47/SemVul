getPathFromFileName(QString fileName)
{
    QString filePath;
    if(fileName.size() > 0)
    {
        std::string path = "";
        clustalw::utilityObject->getPath(fileName.toStdString(), &path);

        if(path.size() > 0)
        {
            filePath = QString(path.c_str());
        }
        else
        {
           filePath = QDir::currentPath() + QString(QDir::separator()) + "temp";
        }
    }
    return filePath;
}

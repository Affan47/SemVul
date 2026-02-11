loadPartsAux(QDir & dir, QStringList & nameFilters, int & loadingPart, int totalPartCount) {

    QFileInfoList list = dir.entryInfoList(nameFilters, QDir::Files | QDir::NoSymLinks);
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        QString path = fileInfo.absoluteFilePath ();

        loadPart(path, false);
		emit loadedPart(++loadingPart, totalPartCount);

    }

    QStringList dirs = dir.entryList(QDir::AllDirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    for (int i = 0; i < dirs.size(); ++i) {
    	QString temp2 = dirs[i];
       	dir.cd(temp2);

		m_loadingContrib = (temp2 == "contrib");

    	loadPartsAux(dir, nameFilters, loadingPart, totalPartCount);
    	dir.cdUp();
    }
}

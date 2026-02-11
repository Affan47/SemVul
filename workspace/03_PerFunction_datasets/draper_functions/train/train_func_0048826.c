scan(const QDir& dir, bool recursive, bool addFiles)
{

	QFileInfoList infos = dir.entryInfoList(QDir::Files | QDir::Dirs
	                                        | QDir::NoDotAndDotDot);


	if (followSymLinks_)
		visitedDirs_.insert(dir.absolutePath());


	QFileInfoList::Iterator itr;
	for (itr = infos.begin(); itr != infos.end(); ++itr) {

		qApp->processEvents();
		if (stop_)
			return false;


		scanned_++;
		if ((scanned_ & 0xff) == 0) {
			if (!progressMessage_.isEmpty()) {
				QString msg = progressMessage_.arg(scanned_)
				                              .arg(fileList_.size());
				emit progress(msg);
			}
			else {
				emit progress(scanned_, fileList_.size());
			}
		}


		QString path = (*itr).filePath();
		if ((*itr).isDir()) {

			if (recursive) {

				if ((*itr).isSymLink()) {
					qDebug() << __func__ << (*itr).absoluteFilePath();


					if (!followSymLinks_
						|| visitedDirs_.contains((*itr).absoluteFilePath())) {
							continue;
					}
				}


				QDir childDir(dir);
				if (!childDir.cd((*itr).fileName()))
					continue;


				if (!path.endsWith('/'))
					path += "/";


				if (!scan(childDir, true, filter_.match(path, addFiles)))
					return false;
			}
		}
		else if (addFiles) {


			if (filter_.match(path, false))
				fileList_.append(path);
		}
	}

	return true;
}

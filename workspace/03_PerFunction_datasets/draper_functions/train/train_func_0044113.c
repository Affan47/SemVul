loadSvg(const QByteArray & contents, const QString & filename, bool findNonConnectors) {
    LoadInfo loadInfo;
    loadInfo.filename = filename;
    loadInfo.findNonConnectors = findNonConnectors;
	return loadAux(contents, loadInfo);
}

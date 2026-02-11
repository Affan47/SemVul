copyFolder( const QString& folderName , const QString& newName )
{
	removeFolder( newName );

	QDir dir( folderName );
	QStringList files = dir.entryList();

	QDir newDir;
	newDir.mkdir (newName);
	for (int i = 0; i < files.size(); ++i)
	{
		QFile::copy( folderName + "/" + files[i] , newName + "/" + files[i] );
	}
}

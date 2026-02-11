selectedFilenames()
{
    DEBUG_BLOCK

    QStringList fileNames;
    const QList<int> indexes = selectedIndexes();

    for( int i=0; i < indexes.size(); i++ )
        fileNames << The::playlist()->trackAt( indexes[i] )->prettyUrl();

    return fileNames;
}

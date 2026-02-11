~CopyMap()
{
    if ( map != NULL )
    {
        delete map;
        delete[] fieldCopied;
    }
    delete[] directionTranslation;
    delete[] playerTranslation;
}

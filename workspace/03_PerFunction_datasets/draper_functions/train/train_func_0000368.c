updateLastModInfo()
{
    helpers::FileInfo fi;

    if (helpers::getFileInfo (&fi, propertyFilename) == 0)
        lastFileInfo = fi;
}

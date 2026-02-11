combineDirAndFilename(OFString &result,
                                            const OFString &dirName,
                                            const OFString &fileName,
                                            const OFBool allowEmptyDirName)
{


    if (!fileName.empty() && (fileName.at(0) == PATH_SEPARATOR))
    {
        result = fileName;
        return result;
    }
#ifdef HAVE_WINDOWS_H
    else if ((fileName.length() >= 3))
    {

        char c = fileName.at(0);
        if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')))
        {
            if (fileName.substr(1, 2) == ":\\")
            {
                result = fileName;
                return result;
            }
        }
    }
#endif


    normalizeDirName(result, dirName, allowEmptyDirName);

    if (!fileName.empty() && (fileName != "."))
    {

        if (!result.empty() && (result.at(result.length() - 1) != PATH_SEPARATOR))
            result += PATH_SEPARATOR;

        result += fileName;
    }
    return result;
}

AddArrayOfElements(TiXmlElement* parent, const char* name, const char* attr, const wxArrayString& array, bool isPath)
{
    if (!array.GetCount())
        return;

    for (unsigned int i = 0; i < array.GetCount(); ++i)
    {
        if (array[i].IsEmpty())
            continue;
        AddElement(parent, name, attr, (isPath ? UnixFilename(array[i], wxPATH_UNIX) : array[i]));
    }
}

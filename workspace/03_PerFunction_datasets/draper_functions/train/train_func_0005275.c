ReserveFileForParsing(const wxString& filename, bool preliminary)
{
    const size_t fileIdx = InsertFileOrGetIndex(filename);
    if (   m_FilesToBeReparsed.count(fileIdx)
        && (!m_FileStatusMap.count(fileIdx) || m_FileStatusMap[fileIdx]==fpsDone) )
    {
        RemoveFile(filename);
        m_FilesToBeReparsed.erase(fileIdx);
        m_FileStatusMap[fileIdx]=fpsNotParsed;
    }

    if (m_FileStatusMap.count(fileIdx))
    {
        FileParsingStatus status = m_FileStatusMap[fileIdx];
        if (preliminary)
        {
            if (status >= fpsAssigned)
                return 0;
        }
        else
        {
            if (status > fpsAssigned)
                return 0;
        }
    }
    m_FilesToBeReparsed.erase(fileIdx);
    m_FileStatusMap[fileIdx] = preliminary ? fpsAssigned : fpsBeingParsed;
    return fileIdx;
}

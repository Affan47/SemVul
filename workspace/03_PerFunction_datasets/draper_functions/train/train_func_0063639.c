AbGetFileSize (
    FILE                    *File)
{
    UINT32                  FileSize;
    long                    Offset;


    Offset = ftell (File);

    if (fseek (File, 0, SEEK_END))
    {
        return (0);
    }

    FileSize = (UINT32) ftell (File);


    if (fseek (File, Offset, SEEK_SET))
    {
        return (0);
    }

    return (FileSize);
}

RemoveFileName(char* Path)


{
    char* FileName;
    ULONG i;

    i = (Path [0] ? (Path[1] == ':' ? 2 : 0) : 0);
    FileName = GetFileName(Path + i);

    if ((FileName != (Path + i)) && (IsSeparator(FileName [-1])))
        FileName--;
    if ((FileName == (Path + i)) && (IsSeparator(FileName [0])))
        FileName++;
    FileName[0] = 0;
}

CurrentFree(FileName aFile, int aLine)
{
    DataMemory data;
    data.File = aFile;
    data.Line = aLine;

    System::Locker l(&_mutex);
    _stackCurrentFree.push(data);
}

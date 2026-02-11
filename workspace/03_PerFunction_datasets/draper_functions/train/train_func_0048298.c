FrameMgrSetBuffer (FrameMgr fm, void* area)
{
    if (fm->area)
        return FmBufExist;
    fm->area = (char *) area;
    return FmSuccess;
}

CPCIDSKBinarySegment(PCIDSKFile *file,
                                           int segment,
                                           const char *segment_pointer,
                                           bool bLoad) :
    CPCIDSKSegment(file, segment, segment_pointer),
    loaded_(false),mbModified(false)
{
    if (true == bLoad)
    {
        Load();
    }
    return;
}

CPCIDSK_ARRAY( PCIDSKFile *file, int segment,
                              const char *segment_pointer )
        : CPCIDSKSegment( file, segment, segment_pointer ),
        loaded_(false),mbModified(false)
{
    MAX_DIMENSIONS = 8;
    Load();
}

checkInterData(const int mode)
{
    if (InterData == NULL)
    {
        if (ImageStatus == EIS_Normal)
        {
            ImageStatus = EIS_MemoryFailure;
            DCMIMAGE_ERROR("can't allocate memory for inter-representation");
        } else
            ImageStatus = EIS_InvalidImage;
    }
    else if (InterData->getData() == NULL)
        ImageStatus = EIS_InvalidImage;
    else if (mode && (ImageStatus == EIS_Normal) && isOriginal )
    {
        const unsigned long count = OFstatic_cast(unsigned long, Columns) * OFstatic_cast(unsigned long, Rows) * NumberOfFrames;
        if ((InterData->getInputCount() != count) && ((InterData->getInputCount() >> 1) != ((count + 1) >> 1)))
        {
            DCMIMAGE_WARN("computed (" << count << ") and stored (" << InterData->getInputCount()
                << ") " << "pixel count differ");
        }
    }
    return (ImageStatus == EIS_Normal);
}

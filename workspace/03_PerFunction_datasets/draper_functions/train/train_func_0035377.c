createDicomImage(unsigned long fstart,
                                         unsigned long fcount) const
{
    if ((Image != NULL) && (fstart < getFrameCount()))
    {
        if ((fcount == 0) || (fstart + fcount > getFrameCount()))
            fcount = getFrameCount() - fstart;
        DiImage *image = Image->createImage(fstart, fcount);
        if (image != NULL)
        {
            DicomImage *dicom = new DicomImage(this, image);
            return dicom;
        }
    }
    return NULL;
}

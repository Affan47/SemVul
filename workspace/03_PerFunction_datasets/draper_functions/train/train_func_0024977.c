createMonoOutputImage(const unsigned long frame,
                                              const int bits)
{
    if ((Image != NULL) && (Image->getMonoImagePtr() != NULL))
    {
        DiImage *image = Image->getMonoImagePtr()->createOutputImage(frame, bits);
        if (image != NULL)
        {
            DicomImage *dicom = new DicomImage(this, image, EPI_Monochrome2);
            return dicom;
        }
    }
    return NULL;
}

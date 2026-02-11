updateImagePixelModuleAttributes(DcmItem &dataset)
{

    delete dataset.remove(DCM_SmallestImagePixelValue);
    delete dataset.remove(DCM_LargestImagePixelValue);


    char buffer[32];
    OFStandard::ftoa(buffer, 15, PixelHeight, OFStandard::ftoa_format_f);
    strcat(buffer, "\\");
    OFStandard::ftoa(strchr(buffer, 0), 15, PixelWidth, OFStandard::ftoa_format_f);

    if (hasPixelSpacing)
        dataset.putAndInsertString(DCM_PixelSpacing, buffer);
    else
        delete dataset.remove(DCM_PixelSpacing);

    if (hasPixelAspectRatio && (PixelWidth != PixelHeight))
        dataset.putAndInsertString(DCM_PixelAspectRatio, buffer);
    else
        delete dataset.remove(DCM_PixelAspectRatio);
}

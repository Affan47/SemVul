camSetMaxROI(CamROI *roi, CamImage *image)
{
    roi->coi=0;
    roi->xOffset=0;
    roi->yOffset=0;
    if (image) {
        roi->width=image->width;
        roi->height=image->height;
    } else {
        roi->width=0;
        roi->height=0;
    }
    return 1;
}

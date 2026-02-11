addPlane(const unsigned int group,
                        const signed int left_pos,
                        const signed int top_pos,
                        const unsigned int columns,
                        const unsigned int rows,
                        const DcmOverlayData &data,
                        const DcmLongString &label,
                        const DcmLongString &description,
                        const EM_Overlay mode)
{
    int status = 0;
    if (AdditionalPlanes && isValidGroupNumber(group))
    {
        unsigned int plane = group;
        status = convertToPlaneNumber(plane, AdditionalPlanes);
        if ((status != 0) && (plane < Data->ArrayEntries))
        {
            if (status == 1)
                ++(Data->Count);
            else if (status == 2)
                delete Data->Planes[plane];
            Data->Planes[plane] = new DiOverlayPlane(group, left_pos, top_pos, columns, rows, data, label, description, mode);
            if (checkPlane(plane, 0))
            {
                if (Data->Planes[plane]->getNumberOfFrames() > Frames)
                    Frames = Data->Planes[plane]->getNumberOfFrames();
            } else {
                delete Data->Planes[plane];
                Data->Planes[plane] = NULL;
                if (status == 1)
                    --(Data->Count);
                status = 0;
            }
        }
    }
    return status;
}

camCopyShift(CamImage* source, CamImage* dest, int shift)
{
    if ((source->depth&CAM_DEPTH_MASK)>8) {
        if ((dest->depth&CAM_DEPTH_MASK)==8) {
            return camCopyShift16to8(source,dest, shift);
        } else return camCopyShift16(source,dest, shift);
    } else {
        if ((dest->depth&CAM_DEPTH_MASK)==8) {
            return camCopyShift8(source,dest, shift);
        } else return camCopyShift8to16(source,dest, shift);
    }
}

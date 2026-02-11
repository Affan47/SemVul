BBLabel(Window,Pointer,BB)


struct ka *Window;
struct o *Pointer;
struct ka *BB;
{
    struct la *LDesc;
    int Len,Hei;
    char Xform;

    LDesc = (struct la *)Pointer->oRep;
    Xform = LDesc->laXform;
    FBTextBB(LDesc->laLabel,&Len,&Hei);

    if (Parameters.kpDoingHardcopy) {
        Len *= Parameters.kpHardcopyTextScale;
        Hei *= Parameters.kpHardcopyTextScale;
    }
    if (Window == View->kvCoarseWindow) {
        Len /= View->kvCoarseRatio;
        Hei /= View->kvCoarseRatio;
    }
    else {
        Len /= View->kvFineRatio;
        Hei /= View->kvFineRatio;
    }
    BB->kaLeft = LDesc->laX;
    BB->kaBottom = LDesc->laY;

    if (Xform & 1) {
        if (Xform & 2) {
            if (!(Xform & 4))
                BB->kaBottom -= Len;
            if (Xform & 8)
                BB->kaLeft -= Hei;
        }
        else {
            if (!(Xform & 8))
                BB->kaLeft -= Hei;
            if (Xform & 4)
                BB->kaBottom -= Len;
        }
        BB->kaRight = BB->kaLeft + Hei;
        BB->kaTop = BB->kaBottom + Len;
    }
    else {
        if (Xform & 2) {
            if (!(Xform & 8))
                BB->kaLeft -= Len;
            if (!(Xform & 4))
                BB->kaBottom -= Hei;
        }
        else {
            if (Xform & 8)
                BB->kaLeft -= Len;
            if (Xform & 4)
                BB->kaBottom -= Hei;
        }
        BB->kaRight = BB->kaLeft + Len;
        BB->kaTop = BB->kaBottom + Hei;
    }
}

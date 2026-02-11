PToL(Window,X,Y)


struct ka *Window;
int *X, *Y;
{
    if (Window == View->kvCoarseWindow) {
        *X = .5+(*X - View->kvCoarseViewport->kaLeft)/
            View->kvCoarseRatio;
        *X += Window->kaLeft;
        *Y = .5+(*Y - View->kvCoarseViewport->kaBottom)/
            View->kvCoarseRatio;
        *Y += Window->kaBottom;
    }
    elif (Window == View->kvFineWindow) {
        *X = .5+(*X - View->kvFineViewport->kaLeft)/
            View->kvFineRatio;
        *X += Window->kaLeft;
        *Y = .5+(*Y - View->kvFineViewport->kaBottom)/
            View->kvFineRatio;
        *Y += Window->kaBottom;
    }
    else {
        *X = *Y = 0;
        return;
    }
}

CDBox(Pointer,Layer,Length,Width,X,Y)

struct o *Pointer;
int *Layer;
int *Length,*Width,*X,*Y;
{

    if (Pointer == NULL)
        return;
    if (Pointer->oType != CDBOX)
        *Layer = *Length = *Width = *X = *Y = 0;
    else {
        *Layer = Pointer->oLayer;
        *Length = Pointer->oRight - Pointer->oLeft;
        *Width = Pointer->oTop - Pointer->oBottom;
        *X = Pointer->oLeft + (*Length >> 1);
        *Y = Pointer->oBottom + (*Width >> 1);
    }
}

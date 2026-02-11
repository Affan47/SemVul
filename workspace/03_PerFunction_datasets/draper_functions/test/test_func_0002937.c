setFillStyle(CanvasStyleBaseImpl* fillStyle)
{
    if (!fillStyle)
        return;
    if (fillStyle->isUnsafe())
        canvas()->markUnsafe();

    activeState().fillStyle = fillStyle;
    dirty |= DrtFill;
}

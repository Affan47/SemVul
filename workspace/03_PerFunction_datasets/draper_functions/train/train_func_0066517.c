quadraticCurveTo(float cpx, float cpy, float x, float y)
{
    if (isPathEmpty())
        return;

    path.quadTo(mapToDevice(cpx, cpy), mapToDevice(x, y));
    emptyPath = false;
}

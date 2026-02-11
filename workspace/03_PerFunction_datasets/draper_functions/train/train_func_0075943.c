bezierCurveTo(float cp1x, float cp1y, float cp2x, float cp2y, float x, float y)
{
    if (isPathEmpty())
        return;

    path.cubicTo(mapToDevice(cp1x, cp1y), mapToDevice(cp2x, cp2y), mapToDevice(x, y));
    emptyPath = false;
}

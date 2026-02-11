fitBelowFloats(int widthToFit, int& availableWidth)
{
    assert(widthToFit > availableWidth);

    int floatBottom;
    int lastFloatBottom = m_height;
    int newLineWidth = availableWidth;
    while (true) {
        floatBottom = nearestFloatBottom(lastFloatBottom);
        if (!floatBottom)
            break;

        newLineWidth = lineWidth(floatBottom);
        lastFloatBottom = floatBottom;
        if (newLineWidth >= widthToFit)
            break;
    }
    if (newLineWidth > availableWidth) {
        m_height = lastFloatBottom;
        availableWidth = newLineWidth;
#ifdef DEBUG_LINEBREAKS
    kDebug(6041) << " new position at " << m_height << " newWidth " << availableWidth;
#endif
    }
}

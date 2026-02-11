getWidth() const
{
    const VisualRun *lastRun = getVisualRun(fRunCount - 1);

    if (lastRun == NULL) {
        return 0;
    }

    le_int32 glyphCount = lastRun->getGlyphCount();
    const float *positions = lastRun->getPositions();

    return (le_int32) positions[glyphCount * 2];
}

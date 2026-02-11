svgCharacterHitsPosition(int x, int y, int& offset) const
{
    SVGChar* charAtPosPtr = closestCharacterToPosition(x, y, offset);
    if (!charAtPosPtr)
        return false;

    SVGChar& charAtPos = *charAtPosPtr;
    RenderStyle* style = renderText()->style(m_firstLine);
    FloatRect glyphRect = calculateGlyphBoundaries(style, offset, charAtPos);

    if (m_reversed)
        offset++;


    if (y < charAtPos.y - glyphRect.height() || y > charAtPos.y)
        return false;


    if (x < charAtPos.x) {
        if (offset > 0 && !m_reversed)
            return true;
        else if (offset < (int) end() && m_reversed)
            return true;

        return false;
    }


    if (x >= charAtPos.x + glyphRect.width() && offset == (int) end())
        return false;


    if (x >= charAtPos.x + glyphRect.width() / 2.0)
        offset += m_reversed ? -1 : 1;

    return true;
}

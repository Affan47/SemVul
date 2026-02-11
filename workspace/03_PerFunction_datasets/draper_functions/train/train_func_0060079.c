chunkPortionCallback(SVGInlineTextBox* textBox, int startOffset, const AffineTransform& chunkCtm,
                              const Vector<SVGChar>::iterator& start, const Vector<SVGChar>::iterator& end)
    {
        RenderStyle* style = textBox->renderText()->style();

        Vector<SVGChar>::iterator closestCharacter = 0;
        unsigned int closestOffset = UINT_MAX;

        for (Vector<SVGChar>::iterator it = start; it != end; ++it) {
            if (it->isHidden())
                continue;

            unsigned int newOffset = textBox->start() + (it - start) + startOffset;
            FloatRect glyphRect = chunkCtm.mapRect(textBox->calculateGlyphBoundaries(style, newOffset, *it));


            if (textBox->m_reversed)
                newOffset = textBox->start() + textBox->end() - newOffset;


            float xDistance = glyphRect.x() + glyphRect.width() / 2.0f - m_x;
            float yDistance = glyphRect.y() - glyphRect.height() / 2.0f - m_y;

            float newDistance = sqrtf(xDistance * xDistance + yDistance * yDistance);
            if (newDistance <= m_distance) {
                m_distance = newDistance;
                closestOffset = newOffset;
                closestCharacter = it;
            }
        }

        if (closestOffset != UINT_MAX) {

            m_character = closestCharacter;
            m_offset = closestOffset;
        }
    }

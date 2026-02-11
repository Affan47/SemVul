rightmostPosition(bool includeOverflowInterior, bool includeSelf) const
{
    int right = RenderFlow::rightmostPosition(includeOverflowInterior, includeSelf);
    if (!includeOverflowInterior && hasOverflowClip())
        return right;
    if (includeSelf && m_overflowWidth > right)
        right = m_overflowWidth;

    if (m_floatingObjects) {
        FloatingObject* r;
        QListIterator<FloatingObject*> it(*m_floatingObjects);
        while ( it.hasNext() ) {
            r = it.next();
            if (!r->noPaint) {
                int rp = r->left + r->node->marginLeft() + r->node->rightmostPosition(false);
           	right = qMax(right, rp);
            }
        }
    }
    right = qMax(right, rightmostAbsolutePosition());

    if (!includeSelf && firstLineBox()) {
        for (InlineRunBox* currBox = firstLineBox(); currBox; currBox = currBox->nextLineBox()) {
            int rp = currBox->xPos() + currBox->width();
            right = qMax(right, rp);
        }
    }

    return right;
}

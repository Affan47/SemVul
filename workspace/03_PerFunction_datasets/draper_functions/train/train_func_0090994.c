paintFloats(PaintInfo& pI, int _tx, int _ty, bool paintSelection)
{
    if (!m_floatingObjects)
        return;

    FloatingObject* r;
    QListIterator<FloatingObject*> it(*m_floatingObjects);
    while ( it.hasNext() ) {
        r = it.next();

        if (r->node->isFloating() && !r->noPaint && !r->node->layer()) {
            PaintAction oldphase = pI.phase;
            if (paintSelection) {
                pI.phase = PaintActionSelection;
                r->node->paint(pI, _tx + r->left - r->node->xPos() + r->node->marginLeft(),
                               _ty + r->startY - r->node->yPos() + r->node->marginTop());
            }
            else {
                pI.phase = PaintActionElementBackground;
                r->node->paint(pI,
                               _tx + r->left - r->node->xPos() + r->node->marginLeft(),
                               _ty + r->startY - r->node->yPos() + r->node->marginTop());
                pI.phase = PaintActionChildBackgrounds;
                r->node->paint(pI,
                               _tx + r->left - r->node->xPos() + r->node->marginLeft(),
                               _ty + r->startY - r->node->yPos() + r->node->marginTop());
                pI.phase = PaintActionFloat;
                r->node->paint(pI,
                               _tx + r->left - r->node->xPos() + r->node->marginLeft(),
                               _ty + r->startY - r->node->yPos() + r->node->marginTop());
                pI.phase = PaintActionForeground;
                r->node->paint(pI,
                               _tx + r->left - r->node->xPos() + r->node->marginLeft(),
                               _ty + r->startY - r->node->yPos() + r->node->marginTop());
                pI.phase = PaintActionOutline;
                r->node->paint(pI,
                               _tx + r->left - r->node->xPos() + r->node->marginLeft(),
                               _ty + r->startY - r->node->yPos() + r->node->marginTop());
            }
            pI.phase = oldphase;
        }
    }
}

collectVerticalBoxCoordinates(InlineRunBox *line,
                                          QVector<QPoint> &pointArray,
                                          bool left, int offset, InlineRunBox **lastline = 0)
{
    InlineRunBox *last = 0;
    offset = left ? -offset:offset;
    for (InlineRunBox* curr = line; curr && !last; curr = left ? curr->prevLineBox() : curr->nextLineBox()) {
        InlineBox *root = curr;

        bool isLast = lineBoxesDisjoint(curr, qAbs(offset), left);
        if (isLast) last = curr;

        if (root != line && !isLast)
            while (root->parent()) root = root->parent();
        QPoint newPnt(curr->xPos() + !left*curr->width() + offset,
                      (left ? root->topOverflow() : root->bottomOverflow()) + offset);
        if (!pointArray.isEmpty()) {
            QPoint lastPnt = pointArray.back();
            if (newPnt.x()>lastPnt.x() && !left)
                pointArray.back().setY( qMin(lastPnt.y(), root->topOverflow()-offset) );
            else if (newPnt.x()<lastPnt.x() && left)
                pointArray.back().setY( qMax(lastPnt.y(), root->bottomOverflow()+offset) );
            QPoint insPnt(newPnt.x(), pointArray.back().y());

            appendPoint(pointArray, insPnt);
        }
        appendPoint(pointArray, newPnt);
    }
    if (lastline) *lastline = last;
}

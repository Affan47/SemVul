drawVerticalLines(QPainter *p, int top, int w, int h)
{
    p->setPen(d->verticalLinesColor);
    for (int x = d->verticalLinesOffset; x < (w - 2); x += d->verticalLinesDistance) {
        p->drawLine(w - x, top, w - x, h + top -1);
    }
}

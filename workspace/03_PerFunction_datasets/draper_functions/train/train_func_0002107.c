mouseMoveEvent(QMouseEvent *e)
{
    if (needLayout)
        layoutItems();

    foreach (const PreviewCursor *c, list)
    {
        if (c->rect().contains(e->pos()))
        {
            if (c != current)
            {
                setCursor(*c);
                current = c;
            }
            return;
        }
    }

    setCursor(Qt::ArrowCursor);
    current = NULL;
}

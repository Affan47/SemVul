collectBorders(QList<CollapsedBorderValue>& borderStyles)
{
    for (RenderObject* curr = firstChild(); curr; curr = curr->nextSibling())
        curr->collectBorders(borderStyles);
}

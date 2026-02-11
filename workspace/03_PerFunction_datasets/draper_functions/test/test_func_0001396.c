setPen(const QPen &pen)
{
    QPen newPen = pen;
    newPen.setCosmetic(true);
    const QPen oldPen = d_ptr->pen;

    if (oldPen == newPen)
        return;

    d_ptr->pen = newPen;
    emit penChanged(newPen);
}

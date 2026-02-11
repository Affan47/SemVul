plotColor() const
{
    if (!rangemode) return QColor(Qt::blue).name();
    else {
        return colorButton->getColor().name();
    }
}

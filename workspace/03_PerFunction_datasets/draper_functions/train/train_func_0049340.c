showTooltip(Q3ListViewItem *item, const QPoint &, int column) const
{
        return ((column==tooltipColumn()) && !tooltip(item, column).isEmpty());
}

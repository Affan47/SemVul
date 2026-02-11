addSplitDirectionItems(QMenu* m)
{
    connect(m, SIGNAL(triggered(QAction*)),
	    this, SLOT(splitActivated(QAction*)) );

    addSplitAction(m, tr("Recursive Bisection"), TreeMapItem::Bisection);
    addSplitAction(m, tr("Columns"), TreeMapItem::Columns);
    addSplitAction(m, tr("Rows"), TreeMapItem::Rows);
    addSplitAction(m, tr("Always Best"), TreeMapItem::AlwaysBest);
    addSplitAction(m, tr("Best"), TreeMapItem::Best);
    addSplitAction(m, tr("Alternate (V)"), TreeMapItem::VAlternate);
    addSplitAction(m, tr("Alternate (H)"), TreeMapItem::HAlternate);
    addSplitAction(m, tr("Horizontal"), TreeMapItem::Horizontal);
    addSplitAction(m, tr("Vertical"), TreeMapItem::Vertical);
}

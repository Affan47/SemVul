regenerateGrid()
{
    widgetAt.clear();

    int columns = cols;
    if (columns == -1)
	columns = (int) ceil(sqrt((float) items.count()));


    if (grid) delete grid;
    grid = new QGridLayout(this);
    grid->setMargin(1);
    grid->setSpacing(0);

    int ccol = 0, crow = 0;
    for (int i = 0; i < items.size(); ++i) {
        if (items.at(i)) {
            widgetAt[crow][ccol] = items.at(i);
            grid->addWidget(items.at(i), crow, ccol++);
            if (ccol == columns) {
                ++crow;
                ccol = 0;
            }
        }
    }

    if (moreButton) {
	grid->addWidget(moreButton, crow, ccol);
	widgetAt[crow][ccol] = moreButton;
    }
    updateGeometry();
}

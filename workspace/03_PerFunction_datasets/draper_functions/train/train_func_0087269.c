resetClicked()
{
    colorSet = GCColor::defaultColorSet();
    colors->clear();
    for (int i=0; colorSet[i].name != ""; i++) {

        QTreeWidgetItem *add;
        ColorButton *colorButton = new ColorButton(this, colorSet[i].name, colorSet[i].color);
        add = new QTreeWidgetItem(colors->invisibleRootItem());
        add->setText(0, colorSet[i].name);
        colors->setItemWidget(add, 1, colorButton);

    }
}

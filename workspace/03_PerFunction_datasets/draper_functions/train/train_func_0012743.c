itemUpdateSound()
{
    QTreeWidgetItem *item;

    item = getItem();
    if (item)
	item->setText(3, soundCheckBox->isChecked() ? "1" : "0");
    if (!lock_modified)
	setModified(true);
}

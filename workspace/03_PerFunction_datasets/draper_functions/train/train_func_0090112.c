refreshCount()
{
    int selected = 0;

    for (int i=0; i<rideList->invisibleRootItem()->childCount(); i++) {
        QTreeWidgetItem *curr = rideList->invisibleRootItem()->child(i);
        QCheckBox *check = (QCheckBox*)rideList->itemWidget(curr, 0);
        if (check->isChecked()) selected++;
    }
    progressLabel->setText(QString("%1 of %2 selected").arg(selected)
                            .arg(rideList->invisibleRootItem()->childCount()));
}

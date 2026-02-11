addClicked()
{

    zonePage->zones.setScheme(zonePage->schemePage->getScheme());


    int index = zonePage->zones.addHrZoneRange(dateEdit->date(), ltEdit->value(), restHrEdit->value(), maxHrEdit->value());


    QTreeWidgetItem *add = new QTreeWidgetItem;
    add->setFlags(add->flags() & ~Qt::ItemIsEditable);
    ranges->invisibleRootItem()->insertChild(index, add);


    add->setText(0, dateEdit->date().toString("MMM d, yyyy"));


    add->setText(1, QString("%1").arg(ltEdit->value()));

    add->setText(2, QString("%1").arg(restHrEdit->value()));

    add->setText(3, QString("%1").arg(maxHrEdit->value()));
}

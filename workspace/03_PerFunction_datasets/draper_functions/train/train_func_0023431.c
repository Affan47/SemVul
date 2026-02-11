associateWidget(QWidget *widget, const QString &operation)
{
    if (!widget) {
        return;
    }

    disassociateWidget(widget);
    d->associatedWidgets.insert(widget, operation);
    connect(widget, SIGNAL(destroyed(QObject*)), this, SLOT(associatedWidgetDestroyed(QObject*)));

    widget->setEnabled(!d->disabledOperations.contains(operation));
}

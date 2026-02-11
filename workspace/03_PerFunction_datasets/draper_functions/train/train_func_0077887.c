setNativeWidget(KComboBox *nativeWidget)
{
    if (widget()) {
        widget()->deleteLater();
    }

    connect(nativeWidget, SIGNAL(activated(QString)), this, SIGNAL(activated(QString)));
    connect(nativeWidget, SIGNAL(currentIndexChanged(int)),
            this, SIGNAL(currentIndexChanged(int)));
    connect(nativeWidget, SIGNAL(currentIndexChanged(QString)),
            this, SIGNAL(textChanged(QString)));

    d->setWidget(nativeWidget);
    nativeWidget->setWindowIcon(QIcon());

    nativeWidget->setAttribute(Qt::WA_NoSystemBackground);
    nativeWidget->setStyle(d->style.data());

    d->syncBorders();
}

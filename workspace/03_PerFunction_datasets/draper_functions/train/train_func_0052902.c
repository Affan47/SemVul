setDefaultWidget( QWidget *widget )
{
    Q_D(KPageView);

    Q_ASSERT(widget);

    bool isCurrent = (d->stack->currentIndex() == d->stack->indexOf( d->defaultWidget ));


    d->stack->removeWidget( d->defaultWidget );
    delete d->defaultWidget;


    d->defaultWidget = widget;
    d->stack->addWidget(d->defaultWidget);

    if (isCurrent)
        d->stack->setCurrentWidget(d->defaultWidget);
}

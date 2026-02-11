fadeCapacityBar(const QModelIndex &index, FadeType fadeType)
{
    QTimeLine *timeLine = delegate->fadeAnimationForIndex(index);
    delete timeLine;
    delegate->removeFadeAnimation(index);
    timeLine = new QTimeLine(250, q);
    connect(timeLine, SIGNAL(valueChanged(qreal)), q, SLOT(_k_capacityBarFadeValueChanged()));
    if (fadeType == FadeIn) {
        timeLine->setDirection(QTimeLine::Forward);
        timeLine->setCurrentTime(0);
    } else {
        timeLine->setDirection(QTimeLine::Backward);
        timeLine->setCurrentTime(250);
    }
    delegate->addFadeAnimation(index, timeLine);
    timeLine->start();
}

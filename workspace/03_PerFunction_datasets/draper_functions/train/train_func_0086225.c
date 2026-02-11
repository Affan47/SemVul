timerEvent(QTimerEvent *)
{
    int activeAnimations = 0;

    AnimationListsIterator i(animationLists);
    while (i.hasNext())
    {
        i.next();
        AnimationList *list = i.value();
        const QAbstractItemView *view = i.key();

        activeAnimations += runAnimations(list, view);
    }

    if (activeAnimations == 0 && timer.isActive())
        timer.stop();
}

}

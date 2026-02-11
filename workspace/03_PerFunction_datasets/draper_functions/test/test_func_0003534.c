addAnimationState(AnimationState *state, const QAbstractItemView *view)
{
    AnimationList *list = animationLists.value(view);


    if (!list)
    {
        connect(view, SIGNAL(destroyed(QObject*)), SLOT(viewDeleted(QObject*)));

        list = new AnimationList;
        animationLists.insert(view, list);
    }

    list->append(state);
}

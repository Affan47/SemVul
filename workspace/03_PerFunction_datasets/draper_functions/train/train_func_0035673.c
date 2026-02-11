animatedElementDestroyed(QObject *o)
{
    QMutableHashIterator<int, ElementAnimationState*> it(animatedElements);
    while (it.hasNext()) {
        it.next();
        if (it.value()->qobj == o) {
            if (timerId) {
                animatedElementsToDelete.insert(it.value());
            } else {
                delete it.value();
            }

            it.remove();
        }
    }
}

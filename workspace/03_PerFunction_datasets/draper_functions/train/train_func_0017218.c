detachedItems() const
{
    QList<ExtenderItem*> result;


    if (!d->applet) {
        return QList<ExtenderItem*>();
    }
    Containment *containment = d->applet.data()->containment();
    if (!containment) {
        return result;
    }

    foreach (Containment *c, containment->corona()->containments()) {
        foreach (Applet *applet, c->applets()) {
            if (applet->d->extender) {
                foreach (ExtenderItem *item, applet->d->extender.data()->attachedItems()) {
                    if (item->d->sourceApplet == d->applet.data() && item->isDetached()) {
                        result.append(item);
                    }
                }
            }
        }
    }

    return result;
}

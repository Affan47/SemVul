item(const QString &name) const
{

    foreach (ExtenderItem *item, d->attachedExtenderItems) {
        if (item->d->sourceApplet == d->applet.data() && item->name() == name) {
            return item;
        }
    }


    if (!d->applet) {
        return 0;
    }

    Containment *containment = d->applet.data()->containment();
    if (!containment) {
        return 0;
    }

    QList<Containment *> containments;
    if (containment->corona()) {
        containments = containment->corona()->containments();
    } else {
        containments << containment;
    }

    foreach (Containment *c, containments) {
        foreach (Applet *applet, c->applets()) {
            if (applet->d->extender) {
                if (applet->d->extender.data() == this) {

                    continue;
                }

                if (!applet->d->extender) {
                    continue;
                }

                foreach (ExtenderItem *item, applet->d->extender.data()->attachedItems()) {
                    if (item->d->sourceApplet == d->applet.data() && item->name() == name) {
                        return item;
                    }
                }
            }
        }
    }

    return 0;
}

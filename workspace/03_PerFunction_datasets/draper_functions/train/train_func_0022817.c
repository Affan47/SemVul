clearCache()
{
    FrameData *frame = d->frames[d->prefix];


    QMutableHashIterator<QString, FrameData*> it(d->frames);
    while (it.hasNext()) {
        FrameData *p = it.next().value();
        if (frame != p) {

            if (p->deref(this)) {
                const QString key = d->cacheId(p, it.key());
                FrameSvgPrivate::s_sharedFrames.remove(key);
                p->cachedBackground = QPixmap();
            }

            it.remove();
        }
    }
}

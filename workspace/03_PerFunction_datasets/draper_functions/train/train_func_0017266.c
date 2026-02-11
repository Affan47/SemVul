startAnimation()
{
    d->storeLastIndex();

    QPropertyAnimation *anim = d->anim.data();
    if (anim) {
        anim->stop();
        d->anim.clear();
    }

    anim = new QPropertyAnimation(this,  "onValueChanged",  this);
    d->anim = anim;
    anim->setDuration(150);

    QRect rect = tabRect(currentIndex());
    QRect lastRect = d->startAnimRect.isNull() ? tabRect(lastIndex())
                                               : d->startAnimRect;
    int x = isHorizontal() ? (int)(lastRect.x() -  (lastRect.x() - rect.x())) : rect.x();
    int y = isHorizontal() ? rect.y() : (int)(lastRect.y() -  (lastRect.y() - rect.y()));
    QSizeF sz = lastRect.size() - (lastRect.size() - rect.size());
    d->currentAnimRect = QRect(x, y, (int)(sz.width()), (int)(sz.height()));

    anim->setStartValue(lastRect);
    anim->setEndValue(d->currentAnimRect);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

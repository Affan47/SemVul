updateClearButton()
{
    if (!d->clearButton) {
        return;
    }
    if (isReadOnly()) {
        d->adjustForReadOnly();
        return;
    }

    const QSize geom = size();
    const int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth,0,this);
    const int buttonWidth = d->clearButton->sizeHint().width();
    const QSize newButtonSize(buttonWidth, geom.height());
    const QFontMetrics fm(font());
    const int em = fm.width("m");


    const bool wideEnough = geom.width() > 4 * em + buttonWidth + frameWidth;

    if (newButtonSize != d->clearButton->size()) {
        d->clearButton->resize(newButtonSize);
    }

    if (d->style) {
        d->style.data()->m_overlap = wideEnough ? buttonWidth + frameWidth : 0;
    }

    if (layoutDirection() == Qt::LeftToRight ) {
        d->clearButton->move(geom.width() - frameWidth - buttonWidth - 1, 0);
    } else {
        d->clearButton->move(frameWidth + 1, 0);
    }

    if (wideEnough != d->wideEnoughForClear) {


        d->wideEnoughForClear = wideEnough;
        updateClearButtonIcon(text());
    }
}

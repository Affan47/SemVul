syncBorders()
{

    qreal left, top, right, bottom;

    background->setElementPrefix("normal");
    background->getMargins(left, top, right, bottom);
    q->setContentsMargins(left, top, right, bottom);


    syncActiveRect();

    if (customFont) {
        q->setFont(q->font());
    } else {
        q->setFont(Theme::defaultTheme()->font(Theme::DefaultFont));
        customFont = false;
    }

    if (q->nativeWidget()->isEditable()) {
        focusIndicator->setFrameSvg(lineEditBackground);
    } else {
        focusIndicator->setFrameSvg(background);
    }
    focusIndicator->setFlag(QGraphicsItem::ItemStacksBehindParent, !q->nativeWidget()->isEditable() || !lineEditBackground->hasElement("hint-focus-over-base"));
}

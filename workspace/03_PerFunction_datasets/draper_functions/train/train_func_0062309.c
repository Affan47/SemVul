subElementRect(SubElement element, const QStyleOption *option, const QWidget *widget) const
{
    switch (element) {
    case SE_LineEditContents: {
        d->createTextBox();

        qreal left, top, right, bottom;
        d->textBox->getMargins(left, top, right, bottom);
        return option->rect.adjusted(left + 2, top + 2, -(right + 2), -(bottom + 2));
    }
    default:
        return qApp->style()->subElementRect(element, option, widget);
    }
}

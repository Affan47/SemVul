setTextSelectable(bool enable)
{
    if (enable) {
        nativeWidget()->setTextInteractionFlags(Qt::TextBrowserInteraction);
    } else {
        nativeWidget()->setTextInteractionFlags(Qt::LinksAccessibleByMouse | Qt::LinksAccessibleByKeyboard);
    }

    d->textSelectable = enable;
}

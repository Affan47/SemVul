setButtonGuiItem(ButtonCode button, const GuiItem &item)
{
    QAbstractButton *b=getButton(button);
    if (b) {
        b->setText(item.text);
        if (!item.icon.isEmpty()) {
            b->setIcon(Icon(item.icon));
        }
    }
}

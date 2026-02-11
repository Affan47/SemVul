addTitle(const QIcon &icon, const QString &text, QAction* before)
{
    QAction *buttonAction = new QAction(this);
    QFont font = buttonAction->font();
    font.setBold(true);
    buttonAction->setFont(font);
    buttonAction->setText(text);
    buttonAction->setIcon(icon);

    QWidgetAction *action = new QWidgetAction(this);
    action->setObjectName(KMENU_TITLE);
    QToolButton *titleButton = new QToolButton(this);
    titleButton->installEventFilter(d);
    titleButton->setDefaultAction(buttonAction);
    titleButton->setDown(true);
    titleButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    action->setDefaultWidget(titleButton);

    insertAction(before, action);
    return action;
}

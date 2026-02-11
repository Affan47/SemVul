enableAction(const QString &name, bool enable)
{
    QAction *action = this->action(name);
    if (action) {
        action->setEnabled(enable);
        action->setVisible(enable);
    }
}

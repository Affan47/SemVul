prepareContainmentActions(const QString &trigger, const QPoint &screenPos, KMenu *menu)
{
    ContainmentActions *plugin = actionPlugins()->value(trigger);
    if (!plugin) {
        return false;
    }
    plugin->setContainment(q);

    if (!plugin->isInitialized()) {
        KConfigGroup cfg = q->containmentActionsConfig();
        KConfigGroup pluginConfig = KConfigGroup(&cfg, trigger);
        plugin->restore(pluginConfig);
    }

    if (plugin->configurationRequired()) {
        KMenu *localMenu = menu ? menu : new KMenu();

        localMenu->addTitle(i18n("This plugin needs to be configured"));
        localMenu->addAction(q->action("configure"));

        if (!menu) {
            localMenu->exec(screenPos);
            delete localMenu;
        }

        return false;
    } else if (menu) {
        QList<QAction*> actions = plugin->contextualActions();
        if (actions.isEmpty()) {


            if (!isPanelContainment() && q->action("configure")) {
                menu->addAction(q->action("configure"));
            }
        } else {
            menu->addActions(actions);
        }
    }

    return true;
}

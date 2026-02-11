remove(KAction *action, Removal removal)
{
    if (!action  || action->objectName().isEmpty()) {
        return;
    }

    const bool isRegistered = actions.contains(action);
    if (!isRegistered) {
        return;
    }

    QStringList actionId = makeActionId(action);

    nameToAction.remove(actionId.at(KGlobalAccel::ActionUnique), action);
    actions.remove(action);

    if (removal == UnRegister) {


        iface.unRegister(actionId);
    } else {


        if (!action->property("isConfigurationAction").toBool()) {

            action->objectName().startsWith(QLatin1String("_k_session:"))
                ? iface.unRegister(actionId)
                : iface.setInactive(actionId);
        }
    }
}

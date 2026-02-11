findAction(const QString &actionName, KXMLGUIClient **clientOut) const
{
    foreach (KXMLGUIClient* client, xmlguiClients) {
        QAction* action = client->actionCollection()->action(actionName);
        if (action) {
            if (clientOut) {
                *clientOut = client;
            }
            return action;
        }
    }
    return 0;
}

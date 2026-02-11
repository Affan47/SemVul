ScriptingPlugin(QObject* parent)
    : KParts::Plugin(parent)
    , d(new ScriptingPluginPrivate())
{
    d->userActionsFile = KGlobal::dirs()->locateLocal("appdata", "scripts/scriptactions.rc");
    d->collectionName="scripting-plugin";
}

toString(ExecState*) const
{
    QString iface;
    if (ScriptableExtension* se = objExtension.data()) {
        iface = QString::fromLatin1(se->metaObject()->className());
    } else {
        iface = QString::fromLatin1("detached");
    }

    if (type == FunctionRef) {
        return QString(QLatin1String("[function ImportedScriptable:") + iface + QLatin1Char('/') + field + QLatin1Char(']'));
    } else {
        return QString(QLatin1String("[object ImportedScriptable:") + iface + QLatin1Char(']'));
    }
}

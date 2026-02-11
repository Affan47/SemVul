registerEnums(QScriptValue &scriptValue, const QMetaObject &meta)
{

    QScriptEngine *engine = scriptValue.engine();
    for (int i = 0; i < meta.enumeratorCount(); ++i) {
        QMetaEnum e = meta.enumerator(i);

        for (int i=0; i < e.keyCount(); ++i) {

            scriptValue.setProperty(e.key(i), QScriptValue(engine, e.value(i)));
        }
    }
}

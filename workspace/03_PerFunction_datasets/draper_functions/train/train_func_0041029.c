parallelAnimationGroup(QScriptContext *context, QScriptEngine *engine)
{
    QObject *parent = extractParent(context, engine);
    if (!parent) {
        return engine->undefinedValue();
    }

    ParallelAnimationGroup *group = new ParallelAnimationGroup(parent);
    return engine->newQObject(group);
}

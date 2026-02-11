setDeclarativeEngine(QDeclarativeEngine *engine)
{
    if (d->declarativeEngine.data() == engine) {
        return;
    }
    d->initialized = false;
    d->declarativeEngine = engine;
}

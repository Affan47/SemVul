initEngineController()
{
    EngineController *controller = new EngineController();
    Components::setEngineController( controller );
    bool invoked = QMetaObject::invokeMethod( controller, "initializePhonon", Qt::DirectConnection );
    Q_ASSERT( invoked );
}

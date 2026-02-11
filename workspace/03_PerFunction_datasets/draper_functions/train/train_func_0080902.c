config()
{
    GlobalGUIConfig* gc;

    if (_config == 0) {
        gc = new GlobalGUIConfig();
        _config = gc;
    }
    else {
        gc = dynamic_cast<GlobalGUIConfig*>(_config);
        if (gc == 0)
            qFatal("Internal error: config object is not a GlobalGUIConfig.");
    }

    return gc;
}

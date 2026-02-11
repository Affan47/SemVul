pbrtCoordSysTransform(const string &name) {
    VERIFY_INITIALIZED("CoordSysTransform");
    if (namedCoordinateSystems.find(name) !=
        namedCoordinateSystems.end())
        curTransform = namedCoordinateSystems[name];
    else
        Warning("Couldn't find named coordinate system \"%s\"",
                name.c_str());
}

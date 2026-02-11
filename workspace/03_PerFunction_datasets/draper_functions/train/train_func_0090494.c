isPluginVersionCompatible(unsigned int version)
{
    if (version == quint32(-1)) {

        kWarning() << "unversioned plugin detected, may result in instability";
        return true;
    }


    const quint32 minVersion = PLASMA_MAKE_VERSION(PLASMA_VERSION_MAJOR, 0, 0);

    if (version < minVersion) {
        kDebug() << "plugin is compiled against incompatible Plasma version  " << version
                 << "This build is compatible with" << PLASMA_VERSION_MAJOR << ".0.0 (" << minVersion
                 << ")";
        return false;
    }

    return true;
}

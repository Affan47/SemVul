fileModule()
{
    if(!s_module) {
        QString moduleName = KConfig("kdeglobals").group(ConfigGroup).readEntry("file module", s_defaultFileModuleName);
        if(!(s_module = loadFileModule(moduleName))) {
            kDebug() << "Failed to load configured file module" << moduleName;
            if(moduleName != s_defaultFileModuleName) {
                kDebug() << "Falling back to default file module.";
                s_module = loadFileModule(s_defaultFileModuleName);
            }
        }
    }
    return s_module;
}

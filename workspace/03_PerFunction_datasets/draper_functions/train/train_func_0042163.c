resolveDependencies(const QList<PluginSpec *> &specs)
{
    if (hasError)
        return false;
    if (state == PluginSpec::Resolved)
        state = PluginSpec::Read;
    if (state != PluginSpec::Read) {
        errorString = QCoreApplication::translate("PluginSpec", "Resolving dependencies failed because state != Read");
        hasError = true;
        return false;
    }
    QHash<PluginDependency, PluginSpec *> resolvedDependencies;
    foreach (const PluginDependency &dependency, dependencies) {
        PluginSpec *found = 0;

        foreach (PluginSpec *spec, specs) {
            if (spec->provides(dependency.name, dependency.version)) {
                found = spec;
                break;
            }
        }
        if (!found) {
            if (dependency.type == PluginDependency::Required) {
                hasError = true;
                if (!errorString.isEmpty())
                    errorString.append(QLatin1Char('\n'));
                errorString.append(QCoreApplication::translate("PluginSpec", "Could not resolve dependency '%1(%2)'")
                    .arg(dependency.name).arg(dependency.version));
            }
            continue;
        }
        resolvedDependencies.insert(dependency, found);
    }
    if (hasError)
        return false;

    dependencySpecs = resolvedDependencies;

    state = PluginSpec::Resolved;

    return true;
}

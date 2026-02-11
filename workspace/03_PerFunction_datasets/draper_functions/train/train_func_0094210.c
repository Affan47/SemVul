loadQueue(PluginSpec *spec, QList<PluginSpec *> &queue,
        QList<PluginSpec *> &circularityCheckQueue)
{
    if (queue.contains(spec))
        return true;

    if (circularityCheckQueue.contains(spec)) {
        spec->d->hasError = true;
        spec->d->errorString = PluginManager::tr("Circular dependency detected:\n");
        int index = circularityCheckQueue.indexOf(spec);
        for (int i = index; i < circularityCheckQueue.size(); ++i) {
            spec->d->errorString.append(PluginManager::tr("%1(%2) depends on\n")
                .arg(circularityCheckQueue.at(i)->name()).arg(circularityCheckQueue.at(i)->version()));
        }
        spec->d->errorString.append(PluginManager::tr("%1(%2)").arg(spec->name()).arg(spec->version()));
        return false;
    }
    circularityCheckQueue.append(spec);

    if (spec->state() == PluginSpec::Invalid || spec->state() == PluginSpec::Read) {
        queue.append(spec);
        return false;
    }


    foreach (PluginSpec *depSpec, spec->dependencySpecs()) {
        if (!loadQueue(depSpec, queue, circularityCheckQueue)) {
            spec->d->hasError = true;
            spec->d->errorString =
                PluginManager::tr("Cannot load plugin because dependency failed to load: %1(%2)\nReason: %3")
                    .arg(depSpec->name()).arg(depSpec->version()).arg(depSpec->errorString());
            return false;
        }
    }

    queue.append(spec);
    return true;
}

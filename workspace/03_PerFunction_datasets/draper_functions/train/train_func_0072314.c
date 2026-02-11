addToExcludedEnvironments(const QString& environment)
{
    QStringList envs = excludedEnvironments();

    if (envs.contains(environment)) {
        return;
    }

    envs.append(environment);
    setExcludedEnvironments(envs);
}

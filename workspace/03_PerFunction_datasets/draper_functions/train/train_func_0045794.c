setEnv(const QString &name, const QString &value, bool overwrite)
{
    QStringList env = environment();
    if (env.isEmpty()) {
        env = systemEnvironment();
        env.removeAll(QString::fromLatin1(DUMMYENV));
    }
    QString fname(name);
    fname.append(QLatin1Char('='));
    for (QStringList::Iterator it = env.begin(); it != env.end(); ++it)
        if ((*it).startsWith(fname)) {
            if (overwrite) {
                *it = fname.append(value);
                setEnvironment(env);
            }
            return;
        }
    env.append(fname.append(value));
    setEnvironment(env);
}

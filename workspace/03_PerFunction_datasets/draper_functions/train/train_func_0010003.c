option(const QString& name, const QVariant& defaultvalue)
{
    if(d->options.contains(name))
        return d->options[name];
    InterpreterInfo* info = Manager::self().interpreterInfo( d->interpretername );
    return info ? info->optionValue(name, defaultvalue) : defaultvalue;
}

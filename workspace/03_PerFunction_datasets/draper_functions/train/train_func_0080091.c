add(const QString& name, const QString& desc, ParamTypes paramType, int group)
{
    QxtCommandOption option;
    option.canonicalName = name;
    option.desc = desc;
    option.paramType = paramType;
    option.group = group;
    qxt_d().options.append(option);
    if (group != -1)
        qxt_d().groups[group].append(&(qxt_d().options.last()));

    alias(name, name);
}

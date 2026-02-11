condition(const Service *srv)
{
    const IPService *ip = IPService::constcast(srv);
    return (ip && !ip->getTOSCode().empty());
}

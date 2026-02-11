ToString( const nServerInfoBase & info )
{
    tString ret;
    ret << info.GetConnectionName() << ":" << info.GetPort();
    return ret;
}

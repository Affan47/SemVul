static_cleanup()
{
    NameInfo::removedb(dbs[0]);
    delete dbs[0];
#if CLICK_USERLEVEL
    NameInfo::removedb(dbs[1]);
    delete dbs[1];
#endif
}

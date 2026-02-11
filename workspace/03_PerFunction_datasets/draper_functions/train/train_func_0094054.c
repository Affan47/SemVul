processLog_action(const boost::format& fmt)
{
    bool stamp = dbglogfile.getStamp();
    dbglogfile.setStamp(false);
    dbglogfile.log(fmt.str());
    dbglogfile.setStamp(stamp);
}

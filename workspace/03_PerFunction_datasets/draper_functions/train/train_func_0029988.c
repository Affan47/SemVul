UpdateStatus(const SchedulerEntry& entry)
{
    std::string status;
    std::ostringstream SQLStatement;

    entry.RetrieveStatus(status);

    SQLStatement << "Update Schedule Set Status = '" << status << "' "
        << "Where IDUrl = " << entry.GetIDSchedule();

    if(Query (SQLStatement.str()) == -1)
        return -1;

    return 0;
}

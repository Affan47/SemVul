issueCommand(const std::string& command)
{
    QString qCommand  = command.c_str();
    if (mHerculesActive)
    {
        mHerculesExecutor->issueFormattedCommand("%s\n", command.c_str());
        setIpled(qCommand);
    }

	outDebug(2, std::cout << "issue command:" << command << std::endl);
   return true;
}

restore()
{
    clear();
    AppSettings->beginGroup("/Engines/");
    QStringList engines = AppSettings->childGroups();
    bool modified = false;
    if(engines.size())
    {
        for(int i = 0; i < engines.size(); ++i)
        {
            QString key = QString::number(i);
            QString name = AppSettings->value(key + "/Name").toString();
            EngineData data(name);
            data.command = AppSettings->value(key + "/Command").toString();
            data.options = AppSettings->value(key + "/Options").toString();
            data.directory = AppSettings->value(key + "/Directory").toString();
            QString protocolName = AppSettings->value(key + "/Protocol").toString();
            if(protocolName == "WinBoard")
            {
                data.protocol = EngineData::WinBoard;
            }
            else
            {
                data.protocol = EngineData::UCI;
            }
            AppSettings->getMap(key + "/OptionValues", data.m_optionValues);
            append(data);
        }
    }
    else
    {
        restoreEmpty();
        modified = true;
    }
    AppSettings->endGroup();
    if(modified)
    {
        save();
    }
}

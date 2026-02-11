PackInstances()
{


    std::set<uint32> InstanceSet;


    QueryResult* result = CharacterDatabase.Query("SELECT id FROM instance");
    if (result)
    {
        do
        {
            Field* fields = result->Fetch();
            InstanceSet.insert(fields[0].GetUInt32());
        }
        while (result->NextRow());
        delete result;
    }

    BarGoLink bar(InstanceSet.size() + 1);
    bar.step();

    uint32 InstanceNumber = 1;

    for (std::set<uint32>::iterator i = InstanceSet.begin(); i != InstanceSet.end(); ++i)
    {
        if (*i != InstanceNumber)
        {
            CharacterDatabase.BeginTransaction();

            CharacterDatabase.PExecute("UPDATE creature_respawn SET instance = '%u' WHERE instance = '%u'", InstanceNumber, *i);
            CharacterDatabase.PExecute("UPDATE gameobject_respawn SET instance = '%u' WHERE instance = '%u'", InstanceNumber, *i);
            CharacterDatabase.PExecute("UPDATE corpse SET instance = '%u' WHERE instance = '%u'", InstanceNumber, *i);
            CharacterDatabase.PExecute("UPDATE character_instance SET instance = '%u' WHERE instance = '%u'", InstanceNumber, *i);
            CharacterDatabase.PExecute("UPDATE instance SET id = '%u' WHERE id = '%u'", InstanceNumber, *i);
            CharacterDatabase.PExecute("UPDATE group_instance SET instance = '%u' WHERE instance = '%u'", InstanceNumber, *i);

            CharacterDatabase.CommitTransaction();
        }

        ++InstanceNumber;
        bar.step();
    }

    sLog.outString(">> Instance numbers remapped, next instance id is %u", InstanceNumber);
    sLog.outString();
}

SaveToDB()
{

    if (instance->IsBattleGroundOrArena())
        return;

    if (!Save())
        return;

    std::string data = Save();
    CharacterDatabase.escape_string(data);

    if (instance->Instanceable())
        CharacterDatabase.PExecute("UPDATE instance SET data = '%s' WHERE id = '%u'", data.c_str(), instance->GetInstanceId());
    else
        CharacterDatabase.PExecute("UPDATE world SET data = '%s' WHERE map = '%u'", data.c_str(), instance->GetId());
}

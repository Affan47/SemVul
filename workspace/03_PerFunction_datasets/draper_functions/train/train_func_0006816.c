getDefaultObjectInstance()
{
    if (defaults_AccountData == 0) {
        defaults_AccountData = new AccountData;
        defaults_AccountData->attr_objtype = "obj";
        defaults_AccountData->attr_pos.clear();
        defaults_AccountData->attr_pos.push_back(0.0);
        defaults_AccountData->attr_pos.push_back(0.0);
        defaults_AccountData->attr_pos.push_back(0.0);
        defaults_AccountData->attr_velocity.clear();
        defaults_AccountData->attr_velocity.push_back(0.0);
        defaults_AccountData->attr_velocity.push_back(0.0);
        defaults_AccountData->attr_velocity.push_back(0.0);
        defaults_AccountData->attr_stamp_contains = 0.0;
        defaults_AccountData->attr_stamp = 0.0;
        defaults_AccountData->attr_parents = std::list<std::string>(1, "account");
        attr_flags_AccountData = new std::map<std::string, int>;
        (*attr_flags_AccountData)[USERNAME_ATTR] = USERNAME_FLAG;
        (*attr_flags_AccountData)[PASSWORD_ATTR] = PASSWORD_FLAG;
        (*attr_flags_AccountData)[CHARACTERS_ATTR] = CHARACTERS_FLAG;
        AdminEntityData::getDefaultObjectInstance();
    }
    return defaults_AccountData;
}

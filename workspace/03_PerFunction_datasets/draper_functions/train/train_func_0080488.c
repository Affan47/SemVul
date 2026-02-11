HandleModifyDrunkCommand(char* args)
{
    if (!*args)
        return false;

    uint8 drunkValue = (uint8)atoi(args);
    if (drunkValue > 100)
        drunkValue = 100;

    if (Player* target = getSelectedPlayer())
        target->SetDrunkValue(drunkValue);

    return true;
}

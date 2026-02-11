DoUseDoorOrButton(ObjectGuid guid, uint32 uiWithRestoreTime, bool bUseAlternativeState)
{
    if (!guid)
    {
        return;
    }

    if (GameObject* pGo = instance->GetGameObject(guid))
    {
        if (pGo->GetGoType() == GAMEOBJECT_TYPE_DOOR || pGo->GetGoType() == GAMEOBJECT_TYPE_BUTTON)
        {
            if (pGo->getLootState() == GO_READY)
            {
                pGo->UseDoorOrButton(uiWithRestoreTime, bUseAlternativeState);
            }
            else if (pGo->getLootState() == GO_ACTIVATED)
            {
                pGo->ResetDoorOrButton();
            }
        }
        else
        {
            script_error_log("Script call DoUseDoorOrButton, but gameobject entry %u is type %u.", pGo->GetEntry(), pGo->GetGoType());
        }
    }
}

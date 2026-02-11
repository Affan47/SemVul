ResetDoorOrButton()
{
    if (m_lootState == GO_READY || m_lootState == GO_JUST_DEACTIVATED)
        { return; }

    SwitchDoorOrButton(false);
    SetLootState(GO_JUST_DEACTIVATED);
    m_cooldownTime = 0;
}

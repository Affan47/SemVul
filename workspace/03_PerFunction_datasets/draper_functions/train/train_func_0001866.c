SwitchDoorOrButton(bool activate, bool alternative )
{
    if (activate)
        SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);
    else
        RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);

    if (GetGoState() == GO_STATE_READY)
        SetGoState(alternative ? GO_STATE_ACTIVE_ALTERNATIVE : GO_STATE_ACTIVE);
    else
        SetGoState(GO_STATE_READY);
}

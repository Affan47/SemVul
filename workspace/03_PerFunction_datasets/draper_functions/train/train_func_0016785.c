SetInstance(PseuInstance *inst)
{
    _movemode = MOVEMODE_MANUAL;
    _instance = inst;
    _mychar = inst->GetWSession()->GetMyChar();
    if(!_mychar)
    {
        logerror("MovementMgr: MyCharacter doesn't exist!");


    }
}

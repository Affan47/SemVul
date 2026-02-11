UnSummon()
{
    CombatStop();
    RemoveAurasDueToSpell(GetSpell());

    if (Unit* owner = GetOwner())
    {
        owner->_RemoveTotem(this);
        owner->RemoveAurasDueToSpell(GetSpell());


        if (owner->GetTypeId() == TYPEID_PLAYER)
        {
            ((Player*)owner)->SendAutoRepeatCancel(this);


            if (Group* pGroup = ((Player*)owner)->GetGroup())
            {
                for (GroupReference* itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
                {
                    Player* Target = itr->getSource();
                    if (Target && pGroup->SameSubGroup((Player*)owner, Target))
                        Target->RemoveAurasDueToSpell(GetSpell());
                }
            }
        }

        if (owner->GetTypeId() == TYPEID_UNIT && ((Creature*)owner)->AI())
            ((Creature*)owner)->AI()->SummonedCreatureDespawn((Creature*)this);
    }


    if (isAlive())
        SetDeathState(DEAD);

    AddObjectToRemoveList();
}

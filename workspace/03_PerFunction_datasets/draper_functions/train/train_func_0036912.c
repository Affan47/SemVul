HandleModPossess(bool apply, bool Real)
{
    if (!Real)
        return;

    Unit* target = GetTarget();


    if (GetCasterGuid() == target->GetObjectGuid())
        return;

    Unit* caster = GetCaster();
    if (!caster || caster->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* p_caster = (Player*)caster;
    Camera& camera = p_caster->GetCamera();

    if (apply)
    {
        target->addUnitState(UNIT_STAT_CONTROLLED);

        target->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED);
        target->SetCharmerGuid(p_caster->GetObjectGuid());
        target->setFaction(p_caster->getFaction());


        camera.SetView(target);

        p_caster->SetCharm(target);
        p_caster->SetClientControl(target, 1);
        p_caster->SetMover(target);

        target->CombatStop(true);
        target->DeleteThreatList();
        target->getHostileRefManager().deleteReferences();

        if (CharmInfo* charmInfo = target->InitCharmInfo(target))
        {
            charmInfo->InitPossessCreateSpells();
            charmInfo->SetReactState(REACT_PASSIVE);
            charmInfo->SetCommandState(COMMAND_STAY);
        }

        p_caster->PossessSpellInitialize();

        if (target->GetTypeId() == TYPEID_UNIT)
        {
            ((Creature*)target)->AIM_Initialize();
        }
        else if (target->GetTypeId() == TYPEID_PLAYER)
        {
            ((Player*)target)->SetClientControl(target, 0);
        }
    }
    else
    {
        p_caster->SetCharm(NULL);

        p_caster->SetClientControl(target, 0);
        p_caster->SetMover(NULL);


        camera.ResetView();

        p_caster->RemovePetActionBar();


        if (m_removeMode == AURA_REMOVE_BY_DELETE)
            return;

        target->clearUnitState(UNIT_STAT_CONTROLLED);

        target->CombatStop(true);
        target->DeleteThreatList();
        target->getHostileRefManager().deleteReferences();

        target->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED);

        target->SetCharmerGuid(ObjectGuid());

        if (target->GetTypeId() == TYPEID_PLAYER)
        {
            ((Player*)target)->setFactionForRace(target->getRace());
            ((Player*)target)->SetClientControl(target, 1);
        }
        else if (target->GetTypeId() == TYPEID_UNIT)
        {
            CreatureInfo const* cinfo = ((Creature*)target)->GetCreatureInfo();
            target->setFaction(cinfo->FactionAlliance);
        }

        if (target->GetTypeId() == TYPEID_UNIT)
        {
            ((Creature*)target)->AIM_Initialize();
            target->AttackedBy(caster);
        }
    }
}

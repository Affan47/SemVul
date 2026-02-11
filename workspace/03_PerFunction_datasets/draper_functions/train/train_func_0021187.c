ChooseDisplayId(const CreatureInfo* cinfo, const CreatureData* data , GameEventCreatureData const* eventData )
{

    if (eventData && eventData->modelid)
        { return eventData->modelid; }


    if (data && data->modelid_override)
        { return data->modelid_override; }


    uint32 display_id = 0;


    if (!cinfo->ModelId[1])
    {
        display_id = cinfo->ModelId[0];
    }
    else
        { display_id = cinfo->ModelId[urand(0, 1)]; }


    if (!display_id)
    {
        sLog.outErrorDb("Call customer support, ChooseDisplayId can not select native model for creature entry %u, model from creature entry 1 will be used instead.", cinfo->Entry);

        if (const CreatureInfo* creatureDefault = ObjectMgr::GetCreatureTemplate(1))
            { display_id = creatureDefault->ModelId[0]; }
    }

    return display_id;
}

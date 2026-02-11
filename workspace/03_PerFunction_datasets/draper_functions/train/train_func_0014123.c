GetWorldObject(ObjectGuid guid)
{
    switch (guid.GetHigh())
    {
        case HIGHGUID_PLAYER:       return GetPlayer(guid);
        case HIGHGUID_GAMEOBJECT:   return GetGameObject(guid);
        case HIGHGUID_UNIT:         return GetCreature(guid);
        case HIGHGUID_PET:          return GetPet(guid);
        case HIGHGUID_DYNAMICOBJECT: return GetDynamicObject(guid);
        case HIGHGUID_CORPSE:
        {

            Corpse* corpse = GetCorpse(guid);
            return corpse && corpse->IsInWorld() ? corpse : NULL;
        }
        case HIGHGUID_MO_TRANSPORT:
        case HIGHGUID_TRANSPORT:
        default:                    break;
    }

    return NULL;
}

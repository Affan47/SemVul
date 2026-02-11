operator()(WorldObject* u)
{
    if (i_typeMask && !u->isType(TypeMask(i_typeMask)))
        return false;
    if (i_entry && u->GetEntry() != i_entry)
        return false;
    if (i_obj->GET_GUID() == u->GET_GUID())
        return false;
    if (!i_obj->IsWithinDistInMap(u, i_range))
        return false;
    if (Unit* unit = u->ToUnit())
    {
#ifdef CMANGOS
        if (!unit->isAlive())
            return false;
#else
        if (!unit->IsAlive())
            return false;
#endif
        if (i_hostile)
        {
            if (const Unit* obj = i_obj->ToUnit())
            {
                if ((i_hostile == 1) != obj->IsHostileTo(unit))
                    return false;
            }
        }
    }
    if (i_nearest)
        i_range = i_obj->GetDistance(u);
    return true;
}

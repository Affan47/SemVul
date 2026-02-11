IsConditionAffectToVars()
{
    set<SymVar* > t;
    init_val->GetAllAffectedVars(t);
    last_val->GetAllAffectedVars(t);
    return !t.empty();
}

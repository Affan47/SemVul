setUnitType(UnitType unit_type)
{

    UnitTable::UnitMap m = _unit_table.units(unit_type);
    UnitTable::UnitMap::iterator iter = m.begin();
    while(iter != m.end()) {
        Glib::ustring text = (*iter).first;
        append_text(text);
        ++iter;
    }
    _type = unit_type;
    set_active_text(_unit_table.primary(unit_type));

    return true;
}

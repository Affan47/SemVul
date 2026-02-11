set_value(CdlTransaction transaction, CdlSimpleValue& val, CdlValueSource source)
{
    CYG_REPORT_FUNCNAME("CdlValuable::set_enabled");
    CYG_REPORT_FUNCARG3XV(this, transaction, source);
    CYG_ASSERTC((source == CdlValueSource_Default) || !has_property(CdlPropertyId_Calculated));
    CYG_PRECONDITION_THISC();
    CYG_PRECONDITION_CLASSC(transaction);

    const CdlValue& old_value = transaction->get_whole_value(this);
    CdlValue        new_value = old_value;
    new_value.set_value(val, source);
    transaction->set_whole_value(this, old_value, new_value);

    CYG_REPORT_RETURN();
}

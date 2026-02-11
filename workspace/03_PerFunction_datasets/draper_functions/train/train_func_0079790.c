check_requires(CdlTransaction transaction)
{
    CYG_REPORT_FUNCNAME("CdlValuable::check_requires");
    CYG_REPORT_FUNCARG2XV(this, transaction);
    CYG_PRECONDITION_THISC();
    CYG_PRECONDITION_CLASSC(transaction);

    std::vector<CdlProperty> requires_properties;
    std::vector<CdlProperty>::const_iterator prop_i;
    get_properties(CdlPropertyId_Requires, requires_properties);
    for (prop_i = requires_properties.begin(); prop_i != requires_properties.end(); prop_i++) {

        CdlProperty_GoalExpression gexpr = dynamic_cast<CdlProperty_GoalExpression>(*prop_i);
        CYG_ASSERT_CLASSC(gexpr);
        this->check_requires(transaction, gexpr);
    }

    CYG_REPORT_RETURN();
}

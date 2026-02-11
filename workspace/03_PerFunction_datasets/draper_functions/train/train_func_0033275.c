check_requires(CdlTransaction transaction, CdlProperty_GoalExpression gexpr)
{
    CYG_REPORT_FUNCNAME("CdlValuable::check_requires (property)");
    CYG_REPORT_FUNCARG3XV(this, transaction, gexpr);
    CYG_PRECONDITION_THISC();
    CYG_PRECONDITION_CLASSC(transaction);
    CYG_ASSERT_CLASSC(gexpr);


    if (!transaction->is_active(this) || !this->is_enabled(transaction)) {
        transaction->clear_conflicts(this, gexpr, &CdlConflict_RequiresBody::test);
        CYG_REPORT_RETURN();
        return;
    }


    try {
        CdlEvalContext context(transaction, this, gexpr);
        if (gexpr->eval(context)) {

            transaction->clear_conflicts(this, gexpr, &CdlConflict_RequiresBody::test);
        } else {

            if (!transaction->has_conflict(this, gexpr, &CdlConflict_RequiresBody::test)) {
                CdlConflict_RequiresBody::make(transaction, this, gexpr);
            }
        }
    } catch(CdlEvalException e) {


        transaction->clear_conflicts(this, gexpr, &CdlConflict_RequiresBody::test);
    }

    CYG_REPORT_RETURN();
}

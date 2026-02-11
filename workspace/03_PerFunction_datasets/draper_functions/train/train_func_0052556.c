clear_conflict(CdlConflict conflict)
{
    CYG_REPORT_FUNCNAME("CdlTransaction::clear_conflict");
    CYG_REPORT_FUNCARG2XV(this, conflict);
    CYG_PRECONDITION_THISC();
    CYG_PRECONDITION_CLASSC(conflict);


    if (this == conflict->transaction) {

        if (conflict->structural) {
            std::list<CdlConflict>::iterator conf_i = std::find(new_structural_conflicts.begin(),
                                                                  new_structural_conflicts.end(), conflict);
            CYG_ASSERTC(conf_i != new_structural_conflicts.end());
            new_structural_conflicts.erase(conf_i);
        } else {
            std::list<CdlConflict>::iterator conf_i = std::find(new_conflicts.begin(), new_conflicts.end(), conflict);
            CYG_ASSERTC(conf_i != new_conflicts.end());
            new_conflicts.erase(conf_i);
        }
        delete conflict;

    } else {
        if (conflict->structural) {
            deleted_structural_conflicts.push_back(conflict);
        } else {
            deleted_conflicts.push_back(conflict);
        }
    }

    CYG_REPORT_RETURN();
}

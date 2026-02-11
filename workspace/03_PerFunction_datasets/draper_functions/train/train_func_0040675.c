resolve_recursion(int level)
{
    CYG_REPORT_FUNCNAMETYPE("CdlTransaction::resolve_recursion", "result %d");
    CYG_REPORT_FUNCARG2XV(this, level);
    CYG_PRECONDITION_THISC();

    bool result = false;
    this->propagate();
    if (0 == new_conflicts.size()) {
        result = true;
        CYG_REPORT_RETVAL(result);
        return result;
    }
    if (level >= inference_recursion_limit) {
        result = false;
        CYG_REPORT_RETVAL(result);
        return result;
    }


    bool solutions_possible = false;
    do {
        this->resolve(level + 1);
        std::list<CdlConflict>::const_iterator conf_i;
        solutions_possible = false;
        for (conf_i = this->new_conflicts.begin(); conf_i != this->new_conflicts.end(); conf_i++) {
            if (!(*conf_i)->has_no_solution()) {
                solutions_possible = true;
            }
        }
    } while(solutions_possible);

    result = (0 == new_conflicts.size());
    CYG_REPORT_RETVAL(result);
    return result;
}

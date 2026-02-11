body()
{
    CYG_REPORT_FUNCNAME("CdlTransaction::body");
    CYG_REPORT_FUNCARG1XV(this);
    CYG_PRECONDITION_THISC();


    CYG_PRECONDITIONC((0 == parent) && (0 != toplevel));

    if (!inference_enabled) {
        this->propagate();
        this->commit();
        CYG_REPORT_RETURN();
        return;
    }

    if (0 == inference_callback) {
        bool progress = false;
        do {
            progress = false;
            this->propagate();
            CYG_LOOP_INVARIANTC(0 == value_changes.size());
            this->resolve();
            if (0 != value_changes.size()) {
                progress = true;
            }
        } while(progress);

        this->commit();
        CYG_REPORT_RETURN();
        return;
    }

    bool cancel = false;

    unsigned int resolved_size = 0;
    unsigned int globals_with_solutions_size = 0;

    do {
        bool progress = false;
        do {
            progress = false;
            this->propagate();
            CYG_LOOP_INVARIANTC(0 == value_changes.size());
            this->resolve();
            if (0 != value_changes.size()) {
                progress = true;
            }
        } while(progress);


        if ((0 == new_conflicts.size()) &&
            (resolved_size == resolved_conflicts.size()) &&
            (globals_with_solutions_size == global_conflicts_with_solutions.size())) {
            cancel = false;
            break;
        }


        if (!this->dirty) {
            cancel = false;
            break;
        }


        this->dirty = false;
        resolved_size = resolved_conflicts.size();
        globals_with_solutions_size = global_conflicts_with_solutions.size();


        if (CdlInferenceCallbackResult_Cancel == (*inference_callback)(this)) {
            cancel = true;
        }
    } while(!cancel);

    if (cancel) {
        this->cancel();
    } else {
        this->commit();
    }

    CYG_REPORT_RETURN();
}

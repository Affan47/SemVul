change_constraints(SEC_base *elem) {
    GB_ERROR  error    = 0;

    GB_CSTR constraint_type = 0;
    GB_CSTR element_type    = 0;

    switch (elem->getType()) {
        case SEC_HELIX:
            constraint_type = "length";
            element_type    = "helix";
            break;
        case SEC_LOOP:
            constraint_type = "radius";
            element_type    = "loop";
            break;
        default:
            sec_assert(0);
            error           = "Illegal element type";
            break;
    }

    if (!error) {
        char *question = GBS_global_string_copy("%s-constraints for %s", constraint_type, element_type);
        char *answer   = aw_input(question, GBS_global_string("%.2f-%.2f", elem->minSize(), elem->maxSize()));

        while (answer) {
            char *end;
            double low = strtod(answer, &end);

            if (end[0]!='-') {
                error = "Wrong format! Wanted format is 'lower-upper'";
            }
            else {
                double high = strtod(end+1, 0);

                if (low<0 || high<0 || (low && high && low>high)) {
                    error = "Illegal values";
                }
                else {
#if defined(DEBUG)
                    sec_assert(!low || !high || low<=high);
#endif
                    elem->setConstraints(low, high);
                    break;
                }
            }

            sec_assert(error);
            aw_popup_ok(error);

            char *retry = aw_input(question, answer);
            free(answer);

            answer = retry;
        }

        free(answer);
        free(question);
    }
    return error;
}

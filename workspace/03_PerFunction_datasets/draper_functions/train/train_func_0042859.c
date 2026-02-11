decide_reconstruct() {
    unsigned int i;

    need_reconstruct = false;
    if (some_child_is_unrecoverable()) {
        if (status == PRESENT) {
            need_reconstruct = true;
        } else if (status == RECOVERABLE) {
            need_present = true;
            for (i=0; i<children.size(); i++) {
                DATA_UNIT& c = *(children[i]);
                if (c.in_recovery_set) {
                    if (c.status == PRESENT) {
                        c.keep_present = true;
                    } else {
                        c.need_present = true;
                    }
                }
            }
        }
    }
    if (needed_by_parent) {
        need_reconstruct = true;
    }
    if (need_reconstruct and !bottom_level) {

        int n = 0;
        for (i=0; i<children.size(); i++) {
            META_CHUNK& c = *(META_CHUNK*)children[i];
            if (c.status == PRESENT) {
                c.needed_by_parent = true;
                n++;
                if (n == coding.n) {
                    break;
                }
            }
        }
    }


    if (keep_present) {
        int n = 0;
        for (i=0; i<children.size(); i++) {
            DATA_UNIT& c = *(children[i]);
            if (c.status == PRESENT) {
                c.keep_present = true;
                n++;
                if (n == coding.n) {
                    break;
                }
            }
        }
    }


    if (!bottom_level) {
        for (i=0; i<children.size(); i++) {
            META_CHUNK& c = *(META_CHUNK*)children[i];
            c.decide_reconstruct();
        }
    }
    return 0;
}

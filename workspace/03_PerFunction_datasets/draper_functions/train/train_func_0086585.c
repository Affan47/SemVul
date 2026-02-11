get_first_at(ED4_SearchPositionType type, int start, int end) const {
    if (is_list()) {
        to_array();
    }

    int l = 0;
    int h = arraySize-1;

    ED4_SearchPosition *pos = 0;
    int m = 0;

    while (l<=h) {
        m = (l+h)/2;
        pos = array[m];
        if (pos->get_end_pos()<start) {
            l = m+1;
        }
        else if (pos->get_start_pos()>end) {
            h = m-1;
        }
        else {
            e4_assert(pos->get_end_pos()>=start && pos->get_start_pos()<=end);
            break;
        }
    }

    if (l>h) {
        return 0;
    }

    if (pos) {
        int best_m = m;

        while (m>0) {
            m--;
            pos = array[m];
            if (pos->get_end_pos()>=start && pos->get_start_pos()<=end) {
                best_m = m;
            }
        }
        pos = array[best_m];

        while (pos) {
            if (type==ED4_ANY_PATTERN || pos->get_whatsFound()==type) {
                break;
            }
            pos = pos->get_next();
        }

        return pos;
    }

    return 0;
}

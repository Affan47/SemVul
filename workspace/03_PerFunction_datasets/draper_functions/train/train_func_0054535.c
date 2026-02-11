get_multilist() const {
        ap_assert(is_multi_match());
        return string(best_full_match->name)+multi_list;
    }

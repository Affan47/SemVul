is_seq_swap(const path_t& apath) {
    const unsigned as(apath.size());
    for (unsigned i(0); (i+1)<as; ++i) {
        if (is_segment_type_indel(apath[i].type) &&
            is_segment_type_indel(apath[i+1].type)) {
            return true;
        }
    }
    return false;
}

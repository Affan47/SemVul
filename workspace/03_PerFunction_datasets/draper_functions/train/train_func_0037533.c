apath_insert_trail_size(const path_t& apath) {
    unsigned val(0);
    const unsigned as(apath.size());
    for (unsigned i(0); i<as; ++i) {
        const path_segment& ps(apath[as-i-1]);
        if ((HARD_CLIP == ps.type) || (SOFT_CLIP == ps.type)) {

        } else if (INSERT == ps.type) {
            val += ps.length;
        } else {
            break;
        }
    }
    return val;
}

dump(std::ostream& os) const {
    typedef stage_pos_t::const_iterator siter;

    os << "stage_pos:\n";
    siter i(_stage_pos.begin()), i_end(_stage_pos.end());
    for (; i!=i_end; ++i) {
        os << "pos: " << i->first << " id: " << i->second << "\n";
    }
}

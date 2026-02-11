operator<<(std::ostream& os,
           const bam_seq_base& bs) {

    const unsigned rs(bs.size());
    for (unsigned i(0); i<rs; ++i) { os << bs.get_char(i); }
    return os;
}

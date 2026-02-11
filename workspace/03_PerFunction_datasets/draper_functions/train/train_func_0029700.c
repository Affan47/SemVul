bam_seq_to_str(const bam_seq_base& bs,
               const unsigned start,
               const unsigned end,
               std::string& s) {
    s.clear();
    for (unsigned i(start); i<end; ++i) s.push_back(bs.get_char(i));
}

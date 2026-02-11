print_known_counts(std::ostream& os,
                   const int min_qscore) const {

    unsigned base_count[N_BASE];
    get_known_counts(base_count,min_qscore);

    for (unsigned b(0); b<N_BASE; ++b) {
        os << '\t' << base_count[b];
    }
}

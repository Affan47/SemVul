print_vcf_alt(const unsigned gt,
              const unsigned ref_gt,
              std::ostream& os) {

    bool is_print(false);
    for (unsigned b(0); b<N_BASE; ++b) {
        if (b==ref_gt) continue;
        if (DIGT::expect2(b,gt)) {
            if (is_print) os << ',';
            os << id_to_base(b);
            is_print=true;
        }
    }
    if (! is_print) os << '.';
}

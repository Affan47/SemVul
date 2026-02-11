print_crispr_row(ofstream & out, deque<char> & crispr, string & seqname, int64_t start, bool pam_right, int species_id) {

    out << seqname << "," << start << ",";

    for ( auto it=crispr.begin(); it != crispr.end(); ++it ) {
        out << *it;
    }

    out << "," << pam_right << "," << species_id << '\n';
}

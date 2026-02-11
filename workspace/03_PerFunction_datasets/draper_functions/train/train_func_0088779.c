print_contig_alignment(const grouper_contig& ctg,
                       std::ostream& os) {
    std::string cigar;
    apath_to_cigar(ctg.path,cigar);
    os << "\tContig alignment: '" << cigar << "'\n";
}

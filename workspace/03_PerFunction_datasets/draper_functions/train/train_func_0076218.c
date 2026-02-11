standardize_ref_seq(const char* ref_seq_file,
                    const char* chr_name,
                    std::string& ref_seq,
                    const pos_t offset) {

    const std::string::size_type ref_size(ref_seq.size());
    for (std::string::size_type i(0); i<ref_size; ++i) {
        const char old_ref(ref_seq[i]);
        char c(old_ref);
        if (islower(c)) c = toupper(c);
        if (! is_valid_base(c)) {
            if (! is_iupac_base(c)) {
                static const char def_chr_name[] = "first-sequence-in-file";
                const char* seq_name(NULL != chr_name ? chr_name : def_chr_name);

                log_os << "ERROR:: Unexpected character in reference sequence.\n";
                log_os << "\treference_sequence_file: '" << ref_seq_file << "'\n";
                log_os << "\tchromosome: '" << seq_name << "'\n";
                log_os << "\tcharacter: '" << old_ref << "'\n";
                log_os << "\tcharacter_decimal_index: " << static_cast<int>(old_ref) << "\n";
                log_os << "\tcharacter_position_in_chromosome: " << (i+1+offset) << "\n";
                exit(EXIT_FAILURE);
            }
            c=elandize_base(c);
        }
        if (c != old_ref) ref_seq[i] = c;
    }
}

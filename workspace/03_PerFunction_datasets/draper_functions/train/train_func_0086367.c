load_metadata(ifstream & text) {
    if ( text.is_open() ) {

        uint8_t endian_test;
        text.read( (char *) &endian_test, sizeof(uint8_t) );

        if ( endian_test != 1 ) {
            throw runtime_error("Endianness of the file does not match your hardware!");
        }


        uint32_t file_version;
        text.read( (char *) &file_version, sizeof(uint32_t) );

        if ( file_version != VERSION )
            throw runtime_error("File is the wrong version! Please regenerate.");

        cerr << "Version is " << VERSION << "\n";


        text.read( (char *) &crispr_data, sizeof(crispr_data) );

        cerr << "Assembly is " << crispr_data.assembly
             << " (" << crispr_data.species << ")" << "\n"
             << "File has " << crispr_data.num_seqs << " sequences" << "\n"
             << "Sequence length is " << crispr_data.seq_length << "\n"
             << "Offset is " << crispr_data.offset << "\n"
             << "Species id is " << int(crispr_data.species_id) << endl;

        uint64_t memory_required = crispr_data.num_seqs * sizeof(uint64_t);
        cerr << "Will require " << (memory_required/1024)/1024 << "MB of memory" << endl;


        if ( memory_required > 3221225472 ) {
            throw runtime_error("More than 3gb of memory required, aborting.");
        }
    }
    else {
        cerr << "ifstream passed to load_metadata is not open" << endl;
        throw runtime_error("Failed to load metadata");
    }
}

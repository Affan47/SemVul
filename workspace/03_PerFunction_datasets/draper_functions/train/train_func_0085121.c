get_crispr(uint64_t id) {

    if ( crispr_data.num_seqs == 0 )
        throw runtime_error( "CRISPRs must be loaded before calling get_crispr" );


    id -= crispr_data.offset;

    if ( id >= crispr_data.num_seqs )
        throw runtime_error( "Index out of range" );

    return util::bits_to_string( get_crispr_int(id), crispr_data.seq_length );
}

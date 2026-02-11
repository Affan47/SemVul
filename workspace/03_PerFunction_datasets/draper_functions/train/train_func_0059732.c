APar_Init() {
    if (inited)
        return;


    inited = true;

    modified_atoms = false;
    alter_original = false;

    svn_build = false;

    source_file = NULL;

    atom_number = 0;
    generalAtomicLevel = 1;

    file_opened = false;
    parsedfile = false;
    move_moov_atom = true;
    moov_atom_was_mooved = false;
    hdlrAtom = NULL;
    udtaAtom = NULL;
    complete_free_space_erasure = false;
    initial_optimize_pass = true;
    psp_brand = false;
    prevent_update_using_padding = false;
    metadata_style = UNDEFINED_STYLE;
    tree_display_only = false;

    max_buffer = 4096 * 125;

    bytes_before_mdat = 0;
    bytes_into_mdat = 0;
    mdat_supplemental_offset = 0;
    removed_bytes_tally = 0;
    new_file_size = 0;
    brand = 0;
    mdatData = 0;

    gapless_void_padding = 0;

    contains_unsupported_64_bit_atom = false;

#if defined (WIN32) || defined (__CYGWIN__)
    max_display_width = 45;
#else
    max_display_width = 75;
#endif

    file_progress_buffer = (char*) calloc(1, sizeof(char) * (max_display_width + 50));

    parsed_prefs = false;
    twenty_byte_buffer = (char *) malloc(sizeof(char) * 20);

    track_codecs = EmployedCodecs();

    UnicodeOutputStatus = UNIVERSAL_UTF8;

    forced_suffix_type = NO_TYPE_FORCING;
}

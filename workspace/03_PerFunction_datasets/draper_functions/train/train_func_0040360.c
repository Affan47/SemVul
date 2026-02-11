generate_binary_output(xlnk_script *sc, const char *output_file)
{
    FILE *fp = NULL;

    static xlnk_script_commandprocmap map[] = {
        { XLNK_OUTPUT_COMMAND, set_output },
        { XLNK_COPY_COMMAND, copy_to_output },
        { XLNK_BANK_COMMAND, write_bank },
        { XLNK_LINK_COMMAND, write_unit },
        { XLNK_PAD_COMMAND, write_pad },
        { XLNK_BAD_COMMAND, NULL }
    };

    bank_size = 0x7FFFFFFF;
    bank_offset = 0;
    bank_origin = 0;
    bank_id = -1;
    pc = 0;

    if (output_file) {
        fp = fopen(output_file, "wb");
        if (fp == NULL)
            err("could not open `%s' for writing", output_file);
    }

    xlnk_script_walk(sc, map, (void *)&fp);

    maybe_pad_bank(sc, sc->first_command, fp);
}

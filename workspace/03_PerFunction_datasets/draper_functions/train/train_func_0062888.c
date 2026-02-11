libjte_set_compression(struct libjte_env *o, char *compression_code)
{
    jtc_t compr = JTE_TEMP_GZIP;

    if (strcmp(compression_code, "default") != 0) {
        if (strcmp(compression_code, "gzip") == 0)
            compr = JTE_TEMP_GZIP;
        else if (strcmp(compression_code, "bzip2") ==0)
            compr = JTE_TEMP_BZIP2;
        else {
            sprintf(o->message_buffer,
                    "libjte: Unknown compression code. Known: gzip bzip2");
            libjte_add_msg_entry(o, o->message_buffer, 0);
            return 0;
        }
    }

#ifndef LIBJTE_WITH_LIBBZ2

    if (compr == JTE_TEMP_BZIP2) {
        sprintf(o->message_buffer,
                "libjte: Usage of libbz2 not enabled at compile time\n");
        libjte_add_msg_entry(o, o->message_buffer, 0);
        return 0;
    }

#endif

    o->jte_template_compression = compr;
    return 1;
}

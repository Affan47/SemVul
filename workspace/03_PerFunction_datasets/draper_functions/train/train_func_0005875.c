qfits_table_interpret_type(
        const char  *   str,
        int         *   nb,
        int         *   dec_nb,
        tfits_type  *   type,
        int             table_type)
{
    char        type_c;

    *dec_nb = 0;
    if (table_type == QFITS_BINTABLE) {
        if (sscanf(str, "%d%c", nb, &type_c) == 0) {

            if (sscanf(str, "%c", &type_c) == 0) {
                qfits_error("cannot interpret this type: %s", str);
                return -1;
            }
            *nb = 1;
        }
        switch(type_c) {
            case 'A': *type = TFITS_BIN_TYPE_A; break;
            case 'B': *type = TFITS_BIN_TYPE_B; break;
            case 'C': *type = TFITS_BIN_TYPE_C; break;
            case 'D': *type = TFITS_BIN_TYPE_D; break;
            case 'E': *type = TFITS_BIN_TYPE_E; break;
            case 'I': *type = TFITS_BIN_TYPE_I; break;
            case 'J': *type = TFITS_BIN_TYPE_J; break;
		    case 'K': *type = TFITS_BIN_TYPE_K; break;
            case 'L': *type = TFITS_BIN_TYPE_L; break;
            case 'M': *type = TFITS_BIN_TYPE_M; break;
            case 'P': *type = TFITS_BIN_TYPE_P; break;
            case 'X': *type = TFITS_BIN_TYPE_X; break;
            default: return -1;
        }
    } else if (table_type == QFITS_ASCIITABLE) {
        if (sscanf(str, "%c%d.%d", &type_c, nb, dec_nb) == 0) {
            qfits_error("cannot interpret this type: %s", str);
            return -1;
        }
        switch(type_c) {
            case 'A': *type = TFITS_ASCII_TYPE_A; break;
            case 'D': *type = TFITS_ASCII_TYPE_D; break;
            case 'E': *type = TFITS_ASCII_TYPE_E; break;
            case 'F': *type = TFITS_ASCII_TYPE_F; break;
            case 'I': *type = TFITS_ASCII_TYPE_I; break;
            default: return -1;
        }
    } else {
        qfits_error("unrecognized table type");
        return -1;
    }
    return 0;
}

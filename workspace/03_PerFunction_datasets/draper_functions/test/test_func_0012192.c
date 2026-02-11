parse_xim(char *buff, void *state)
{
#ifdef USE_XIM
    if ((*buff == SPIFCONF_BEGIN_CHAR) || (*buff == SPIFCONF_END_CHAR)) {
        return NULL;
    }
    if (!BEG_STRCASECMP(buff, "input_method ")) {
        RESET_AND_ASSIGN(rs_input_method, spiftool_get_word(2, buff));
    } else if (!BEG_STRCASECMP(buff, "preedit_type ")) {
        RESET_AND_ASSIGN(rs_preedit_type, spiftool_get_word(2, buff));
    } else {
        libast_print_error("Parse error in file %s, line %lu:  Attribute \"%s\" is not valid within context xim\n",
                    file_peek_path(), file_peek_line(), buff);
    }
#else
    libast_print_warning("XIM support was not compiled in, ignoring entire context\n");
    file_poke_skip(1);
#endif
    return state;
    buff = NULL;
}

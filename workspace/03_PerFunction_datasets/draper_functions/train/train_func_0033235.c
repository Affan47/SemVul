epr_parse_double_token(EPR_SPtrArray* header_values, char* token_value, uint* num_elems, uint* num_bytes, EPR_EDataTypeId* tp)
{
    char exceptions[] = EPR_HEADER_EXCEPTIONS_ARRAY;
    char * token_value_o;
    char * tmp;
    uint pos_value = 0;
    int cyc = 0;

    pos_value = 0;
    *num_elems = 0;
    while ((tmp = epr_str_tok_tok(token_value + 1, "+-", exceptions, &pos_value)) != NULL) {
        cyc ++;
        token_value_o = epr_create_string(strlen(tmp) + 1);
        if (strlen(tmp) == strlen(token_value) - 1) {
            token_value_o[0] = token_value[0];
        } else if (pos_value < (uint)strlen(token_value) - 1) {
            token_value_o[0] = token_value[pos_value - strlen(tmp) - 1];
        } else {
            token_value_o[0] = token_value[pos_value - strlen(tmp)];
        }
        strcat(token_value_o, tmp);
        epr_add_ptr_array_elem(header_values, token_value_o);
        epr_free_string(tmp);
    }
    *num_bytes = sizeof(double);
    *tp = e_tid_double;
    *num_elems = cyc;
}

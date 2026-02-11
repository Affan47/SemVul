parse_client_specifier(Octstr **address, long pos,
                                   long *type_of_address)
{
    Octstr *type_value;

    type_value = octstr_create("");

    if ((pos = parse_type(address, &type_value, pos)) < 0) {
        goto parse_error;
    }

    pos = drop_character(address, pos);

    if ((pos = parse_constant("/TYPE", address, pos)) < 0) {
        debug("wap.push.pap.compiler", 0, "PAP COMPILER: constant TYPE"
              " missing from the client address");
        goto parse_error;
    }

    if (octstr_case_compare(type_value, octstr_imm("USER")) == 0) {
        *type_of_address = ADDR_USER;
        goto not_implemented;
    }

    if ((pos = parse_ext_qualifiers(address, pos, type_value)) < 0) {
        goto parse_error;
    }

    if (octstr_case_compare(type_value, octstr_imm("PLMN")) == 0) {
        *type_of_address = ADDR_PLMN;
        pos = parse_global_phone_number(address, pos);
    }

    else if (octstr_case_compare(type_value, octstr_imm("IPv4")) == 0) {
        *type_of_address = ADDR_IPV4;
        pos = parse_ipv4(address, pos);
    }

    else if (octstr_case_compare(type_value, octstr_imm("IPv6")) == 0) {
        *type_of_address = ADDR_IPV6;
        pos = parse_ipv6(address, pos);
    }

    else if (wina_bearer_identifier(type_value)) {
        *type_of_address = ADDR_WINA;
        pos = parse_escaped_value(address, pos);
    }

    else {
        debug("wap.push.pap.compiler", 0, "PAP COMPILER: wrong address type"
              " in the client address");
        goto parse_error;
    }

    octstr_destroy(type_value);
    return pos;

not_implemented:
    octstr_destroy(type_value);
    return -1;

parse_error:
    octstr_destroy(type_value);
    return -2;
}

parse_bad_message_response_value(Octstr *attr_name,
                                            Octstr *attr_value, WAPEvent **e)
{
    if (octstr_compare(attr_name, octstr_imm("code")) == 0) {
	(**e).u.Bad_Message_Response.code = parse_code(attr_value);
        return 0;
    } else if (octstr_compare(attr_name, octstr_imm("desc")) == 0) {
	(**e).u.Bad_Message_Response.desc = octstr_duplicate(attr_value);
        return 0;
    } else if (octstr_compare(attr_name,
	    octstr_imm("bad-message-fragment")) == 0) {
        (**e).u.Bad_Message_Response.bad_message_fragment =
            octstr_duplicate(attr_value);
        return 0;
    }

    debug("wap.push.pap.compiler", 0, "PAP COMPILER: unknown bad message"
          " response element attribute");
    return -2;
}

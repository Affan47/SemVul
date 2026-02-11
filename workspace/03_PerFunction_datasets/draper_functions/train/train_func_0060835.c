generate_broadcast_receive_master(ast_id* id, gm_code_writer& Body, int reduce_op_type) {

    get_main()->generate_lhs_id(id);
    Body.push(" = ");
    bool need_paren = false;

    if (reduce_op_type != GMREDUCE_NULL) {
        if (reduce_op_type == GMREDUCE_MIN) {
            need_paren = true;
            Body.push("Math.min(");
            get_main()->generate_rhs_id(id);
            Body.push(",");
        } else if (reduce_op_type == GMREDUCE_MAX) {
            need_paren = true;
            Body.push("Math.max(");
            get_main()->generate_rhs_id(id);
            Body.push(",");
        } else {
            get_main()->generate_rhs_id(id);
            switch (reduce_op_type) {
                case GMREDUCE_PLUS:
                    Body.push("+");
                    break;
                case GMREDUCE_MULT:
                    Body.push("*");
                    break;
                case GMREDUCE_AND:
                    Body.push("&&");
                    break;
                case GMREDUCE_OR:
                    Body.push("||");
                    break;
                default:
                    assert(false);
                    break;
            }
        }
    }

    Body.push("((");
    generate_broadcast_variable_type(id->getTypeSummary(), Body, reduce_op_type);
    Body.push(") ");
    Body.push("getGlobalObjectsMap().getGlobalObject(");
    Body.push(create_key_string(id));
    Body.push("))");
    Body.push(".getValue().getValue()");
    if (need_paren) Body.push(")");
    Body.pushln(";");
}

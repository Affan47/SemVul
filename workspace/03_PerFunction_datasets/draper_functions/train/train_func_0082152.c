postfix_expression(int mode, Value * v) {
    primary_expression(mode, v);
    for (;;) {
        if (text_sy == '.') {
            next_sy();
            op_field(mode, v);
        }
        else if (text_sy == '[') {
            next_sy();
            op_index(mode, v);
            if (text_sy != ']') {
                error(ERR_INV_EXPRESSION, "']' expected");
            }
            next_sy();
        }
        else if (text_sy == SY_REF) {
            next_sy();
            op_deref(mode, v);
            op_field(mode, v);
        }
        else {
            break;
        }
    }
}

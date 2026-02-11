execute(const opcode_ty *op, opcode_context_ty *icp)
{
    string_list_ty  *left;
    string_list_ty  *right;
    size_t          j;
    string_ty       *s;

    trace(("opcode_catenate::execute()\n{\n"));
    (void)op;


    right = opcode_context_string_list_pop(icp);
    left = opcode_context_string_list_pop(icp);

    switch ((left->nstrings ? 1 : 0) | (right->nstrings ? 2 : 0))
    {
    case 0:

        break;

    case 1:

        for (j = 0; j < left->nstrings; j++)
            opcode_context_string_push(icp, left->string[j]);
        break;

    case 2:

        for (j = 0; j < right->nstrings; j++)
            opcode_context_string_push(icp, right->string[j]);
        break;

    case 3:

        for (j = 0; j < left->nstrings - 1; j++)
            opcode_context_string_push(icp, left->string[j]);
        s = str_catenate(left->string[j], right->string[0]);
        opcode_context_string_push(icp, s);
        str_free(s);
        for (j = 1; j < right->nstrings; j++)
            opcode_context_string_push(icp, right->string[j]);
        break;
    }
    string_list_delete(left);
    string_list_delete(right);
    trace(("return success;\n"));
    trace(("}\n"));
    return opcode_status_success;
}

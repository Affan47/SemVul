execute(const opcode_ty *op, opcode_context_ty *icp)
{
    const opcode_string_ty *this;
    const match_ty  *mp;

    trace(("opcode_string::execute()\n{\n"));
    this = (const opcode_string_ty *)op;


    mp = opcode_context_match_top(icp);
    if (mp)
    {
        string_ty       *s;

        s = match_reconstruct_rhs(mp, this->value, &this->pos);
        if (!s)
        {
            trace(("return error;\n"));
            trace(("}\n"));
            return opcode_status_error;
        }
        opcode_context_string_push(icp, s);
        str_free(s);
    }
    else
        opcode_context_string_push(icp, this->value);
    trace(("return success;\n"));
    trace(("}\n"));
    return opcode_status_success;
}

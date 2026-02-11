print_operand_only_three_type(Operand *o)
{
    switch (o->kind) {
    case KIND_VAR:
        mfprintf(stdout, "V%d", o->entry);
        break;
    case KIND_ARRAY:
        mfprintf(stdout, "A%d", o->entry);
        break;
    case KIND_TEMP:
        mfprintf(stdout, "T%d", o->entry);
        break;
    case KIND_CONST:
        mfprintf(stdout, "C%d", o->entry);
        break;
    default:
        mfprintf(stdout, "Unknown%d", o->entry);
        break;
    }
}

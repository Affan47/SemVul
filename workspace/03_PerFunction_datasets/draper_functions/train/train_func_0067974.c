csbe_get_operand_name(Operand *op)
{
    switch(op->kind){
    case KIND_VAR:
        return(op->tbl.v->name);
    case KIND_ARRAY:
        return(op->tbl.a->name);
    default:
        fprintf(stderr,
                "ERROR(csbe_get_operand_name): not implemented kind: %s\n",
                str_kind[op->kind]);
        exit(1);
    }
}

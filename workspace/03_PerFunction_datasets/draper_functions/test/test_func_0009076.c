write_expr_eval_routine_list(FILE *file, const char *iface)
{
    struct expr_eval_routine *eval;
    struct expr_eval_routine *cursor;
    unsigned short callback_offset = 0;

    fprintf(file, "static const EXPR_EVAL ExprEvalRoutines[] =\n");
    fprintf(file, "{\n");

    LIST_FOR_EACH_ENTRY_SAFE(eval, cursor, &expr_eval_routines, struct expr_eval_routine, entry)
    {
        print_file(file, 1, "%s_%sExprEval_%04u,\n",
                   eval->iface ? eval->iface->name : iface, eval->name, callback_offset);
        callback_offset++;
        list_remove(&eval->entry);
        free(eval->name);
        free(eval);
    }

    fprintf(file, "};\n\n");
}

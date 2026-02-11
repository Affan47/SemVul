expr_value(const char *expression)
{
    Program *prog;
    Value *result;
    conString *str;

    if (!expression) return shareval(val_blank);
    str = CS(Stringnew(expression, -1, 0));
    if (!(prog = compile_tf(str, 0, -1, 1, 0))) return NULL;
    result = prog_interpret(prog, 1);
    prog_free(prog);
    return result;
}

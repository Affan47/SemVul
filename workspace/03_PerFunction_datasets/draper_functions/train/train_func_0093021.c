f_columnhead(union argument *arg)
{
    static char placeholder[] = "@COLUMNHEAD00@";
    struct value a;

    if (!evaluate_inside_using)
	int_error(c_token-1, "columnhead() called from invalid context");

    (void) arg;
    (void) pop(&a);
    column_for_key_title = (int) real(&a);
    snprintf(placeholder+11, 4, "%02d@", column_for_key_title);
    push(Gstring(&a, placeholder));
}

check_for_default(stmt_rule_ty *this)
{
    static string_ty *dot_default;

    trace(("check_for_default()\n{\n"));
    if (!dot_default)
        dot_default = str_from_c(".DEFAULT");
    if
    (
        this->target->length == 1
    &&
        str_equal(this->target->list[0]->text, dot_default)
    )
    {
        str_free(this->target->list[0]->text);
        this->target->list[0]->text = str_from_c("%0%");
    }
    trace(("}\n"));
}

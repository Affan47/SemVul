check_for_ignore(stmt_rule_ty *this)
{
    static string_ty *dot_ignore;

    trace(("check_for_ignore()\n{\n"));
    if (!dot_ignore)
        dot_ignore = str_from_c(".IGNORE");
    if
    (
        this->target->length == 1
    &&
        str_equal(this->target->list[0]->text, dot_ignore)
    )
    {
        this->fake = fake_ignore;
    }
    trace(("}\n"));
}

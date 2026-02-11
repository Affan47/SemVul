check_def(const type_t *t)
{
    if (t->defined)
        error_loc("%s: redefinition error; original definition was at %s:%d\n",
                  t->name, t->loc_info.input_name, t->loc_info.line_number);
}

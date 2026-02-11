use_check(const Element* target, const Def_use_table* def)
{
    if  (def != NULL) {
        while  (target != NULL) {
            if  (use_check_sub_script(target->sub_script, def)) {
                return  TRUE;
            }
            target = target->next_dim;
        }
    }
    return  FALSE;
}

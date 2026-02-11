use_check_sub_script(const Sub_data* target, const Def_use_table* def)
{
    if  (def == NULL) {
        return  FALSE;
    } else {
        while  (target != NULL) {
            if  (target->kind == def->table  &&  target->entry == def->entry) {
                if  (def->table != KIND_ARRAY
                     ||  array_depend_p2(target->op, def->sub_id_ptr)) {
                    return  TRUE;
                }
            } else if  (target->kind == KIND_ARRAY) {
                int  i;
                for  (i=0; i<target->op->nsub; i++) {
                    if  (use_check_sub_script(target->op->sub[i], def)) {
                        return  TRUE;
                    }
                }
            }
            target = target->next;
        }
        return  FALSE;
    }
}

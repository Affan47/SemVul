fli_insert_composite( FL_OBJECT * obj,
                      FL_OBJECT * before )
{
    FL_OBJECT *tmp;

    for ( tmp = obj->child; tmp; tmp = tmp->nc )
    {
        tmp->parent = obj;
        fli_insert_object( tmp, before );
    }
}

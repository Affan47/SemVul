fli_add_composite( FL_OBJECT * obj )
{
    FL_FORM *form = obj->form;
    FL_OBJECT *tmp;

    for ( tmp = obj->child; tmp; tmp = tmp->nc )
    {
        tmp->parent = obj;
        fl_add_object( form, tmp );
    }
}

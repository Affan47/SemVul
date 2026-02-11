compare_pa_object(Pa_object *obj1, Pa_object *obj2)
{
    if (obj1 == NULL || obj2 == NULL)
        return FALSE;

    return ((obj1->kind == obj2->kind)
            && (obj1->entry == obj2->entry));
}

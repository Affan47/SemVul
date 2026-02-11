get_num_of_obj(Pa_object *pa_object_list)
{
    int num;

    Pa_object *obj;

    for (num = 0, obj = pa_object_list;
         obj != NULL;
         num++, obj = obj->next);

    return num;
}

copy_array_usage_list(List *list)
{
    List *new_list = NULL;
    List *li;
    ArrayUsage *au, *new_au;

    for(li = list; li != NULL; li = li->next){
	au = (ArrayUsage *)li->data;
	new_au = copy_array_usage(au);
	new_list = list_append(new_list, new_au);
    }

    return new_list;
}

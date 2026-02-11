list_foreach(List *list,
                  void (*func)(void *data, void *user_data),
                  void *user_data)
{
    List *i;

    for (i = list; i != NULL; i = i->next) {
        func(i->data, user_data);
    }
}

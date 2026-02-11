tlg_no_decriment(List *tlg_list)
{
    List *li;
    Tlg  *tlg;
    for (li = tlg_list; li != NULL; li = li->next)
    {
        tlg = li->data;
        tlg->no--;
    }
}

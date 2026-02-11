octstr_strip_char(Octstr *text, char ch)
{
    int start = 0;

    seems_valid(text);
    gw_assert(!text->immutable);


    while ((ch == octstr_get_char(text, start)) &&
           start <= octstr_len(text))
        start ++;

    if (start > 0)
        octstr_delete(text, 0, start);

    seems_valid(text);
}

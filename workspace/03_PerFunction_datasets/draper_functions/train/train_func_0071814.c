octstr_strip_crlfs(Octstr *text)
{
    int start = 0, end, len = 0;

    seems_valid(text);
    gw_assert(!text->immutable);


    while (iscrlf(octstr_get_char(text, start)) &&
	   start <= octstr_len(text))
        start ++;

    if (start > 0)
        octstr_delete(text, 0, start);


    if ((len = octstr_len(text)) > 0) {
        end = len = len - 1;
        while (iscrlf(octstr_get_char(text, end)) && end >= 0)
            end--;
        octstr_delete(text, end + 1, len - end);
    }

    seems_valid(text);
}

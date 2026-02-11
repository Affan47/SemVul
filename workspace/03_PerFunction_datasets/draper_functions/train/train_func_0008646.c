skip_html_comment(Octstr *html, long *pos)
{
    long i;

    *pos += 4;
    i = octstr_search(html, octstr_imm("-->"), *pos);
    if (i == -1)
        *pos = octstr_len(html);
    else
        *pos = i;
}

find_charset_encoding(Octstr *document)
{
    long gt = 0, enc = 0;
    Octstr *encoding = NULL, *temp = NULL;

    enc = octstr_search(document, octstr_imm(" encoding="), 0);
    gt = octstr_search(document, octstr_imm("?>"), 0);


    if (enc < 0 || enc + 10 > gt)
        return NULL;

	temp = octstr_copy(document, enc + 10, gt - (enc + 10));
    octstr_strip_blanks(temp);
    encoding = octstr_copy(temp, 1, octstr_len(temp) - 2);
    octstr_destroy(temp);

    return encoding;
}

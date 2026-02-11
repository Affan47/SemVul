octstr_convert_from_html_entities(Octstr* input)
{
    int startpos = 0, endpos;
    int entity;
    Octstr *match;

    while ((startpos = octstr_search_char(input, '&', startpos)) != -1) {
        endpos = octstr_search_char(input, ';', startpos + 1);
        if (endpos >= 0) {
            match = octstr_copy(input, startpos + 1, endpos - startpos - 1);
            entity = octstr_find_entity(match, 0, 0);
            if (entity >= 0) {
                octstr_delete(input, startpos, endpos - startpos + 1);
                octstr_insert_char(input, startpos, entity);
            }
            octstr_destroy(match);
        }
        startpos++;
    }
}

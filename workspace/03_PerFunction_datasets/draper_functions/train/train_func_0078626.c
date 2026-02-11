artifact_msg(int level, size_t booksize) {
    const artifactlist *al;
    const artifact *art;
    int i, type, index;
    int book_entries = level > 5 ? RANDOM()%3+RANDOM()%3+2 : RANDOM()%level+1;
    StringBuffer *desc, *message = stringbuffer_new();


    if (book_entries > 5)
        book_entries = 5;


    i = 0;
    do {
        index = RANDOM()%arraysize(art_name_array);
        type = art_name_array[index].type;
        al = find_artifactlist(type);
        i++;
    } while (al == NULL && i < 10);

    if (i == 10) {
        stringbuffer_append_string(message, "None");
        return message;
    }


    art = al->items;
    for (i = RANDOM()%level+RANDOM()%2+1; i > 0; i--) {
        if (art == NULL)
            art = al->items;
        art = art->next;
    }


    stringbuffer_append_printf(message, "Herein %s detailed %s...\n", book_entries > 1 ? "are" : "is", book_entries > 1 ? "some artifacts" : "an artifact");

    i = 0;


    while (book_entries > 0) {
        int with_message;
        if (art == NULL)
            art = al->items;
        with_message = (art->item->msg && RANDOM()%4+1 < level) ? 1 : 0;

        desc = artifact_describe(art, al, with_message, index, i++);

        if (stringbuffer_length(message) + stringbuffer_length(desc) >= booksize) {
            stringbuffer_delete(desc);
            break;
        }

        stringbuffer_append_stringbuffer(message, desc);
        stringbuffer_delete(desc);

        art = art->next;
        book_entries--;
    }

    return message;
}

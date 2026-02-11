add_author(object *op, int msgtype) {
    char title[MAX_BUF];
    const char *name;

    if (msgtype < 0 || strlen(op->msg) < 5)
        return;

    switch (msgtype) {
    case MSGTYPE_MONSTER:
        name = mon_author[RANDOM()%arraysize(mon_author)];
        break;

    case MSGTYPE_ARTIFACT:
        name = art_author[RANDOM()%arraysize(art_author)];
        break;

    case MSGTYPE_SPELLPATH:
        name = path_author[RANDOM()%arraysize(path_author)];
        break;

    case MSGTYPE_ALCHEMY:
        name = formula_author[RANDOM()%arraysize(formula_author)];
        break;

    case MSGTYPE_GODS:
        name = gods_author[RANDOM()%arraysize(gods_author)];
        break;

    case MSGTYPE_MSGFILE:
    default:
        name = book_author[RANDOM()%arraysize(book_author)];
    }

    snprintf(title, sizeof(title), "of %s", name);
    op->title = add_string(title);
}

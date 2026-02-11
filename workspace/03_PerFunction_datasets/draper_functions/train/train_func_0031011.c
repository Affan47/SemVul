add_title(const char *title)
{
    CARD *card, *p, *q;

    for (p = all_cards, q = 0; p != 0; q = p, p = p->link) {
	int cmp = strcmp(p->title, title);
	if (cmp == 0)
	    return p;
	if (cmp > 0)
	    break;
    }

    card = typeCalloc(CARD, 1);
    card->title = strdup(title);
    card->content = strdup("");

    if (q == 0) {
	card->link = all_cards;
	all_cards = card;
    } else {
	card->link = q->link;
	q->link = card;
    }

    return card;
}

DoRemove(Interactor* i) {
    Card* card = cards->next;
    while (card != cards) {
	if (card->i == i) {
            card->prev->next = card->next;
            card->next->prev = card->prev;
	    delete card;
            --perspective->width;
            --perspective->height;
            FixPerspective();
	    break;
	} else {
	    card = card->next;
	}
    }
}

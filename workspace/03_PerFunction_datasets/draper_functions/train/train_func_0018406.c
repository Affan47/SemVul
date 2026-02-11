cards_image_from_file(const gchar *file)
{
	CardsImage *cards;

	cards = g_new(CardsImage, 1);
	cards->preimage = preimage_new_from_file(file);
	cards->width = cards->preimage->width / 13;
	cards->height = cards->preimage->height / 5;
	cards->ratio = (gdouble)cards->width / (gdouble)cards->height;
	cards->pixbuf = NULL;
	cards_image_set_size(cards, cards->width, cards->height);

	return cards;
}

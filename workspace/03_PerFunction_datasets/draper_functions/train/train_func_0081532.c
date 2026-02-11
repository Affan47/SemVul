tweenColorTest (void *element, void *key)
{
	tweencolor_t *a = (tweencolor_t *) element;
	tweencolorkey_t *b = (tweencolorkey_t *) key;

	return (a->pixel == b->pixel
	        && a->bgcolor == b->bgcolor
	        && a->fgcolor == b->fgcolor && a->im == b->im);
}

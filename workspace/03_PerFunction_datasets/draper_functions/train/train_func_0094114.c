gg_svg_free_clip (struct gg_svg_clip *p)
{

    struct gg_svg_item *pi;
    struct gg_svg_item *pin;
    if (p->id != NULL)
	free (p->id);
    pi = p->first;
    while (pi)
      {
	  pin = pi->next;
	  gg_svg_free_item (pi);
	  pi = pin;
      }
    free (p);
}

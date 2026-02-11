MakeContainer(button_info *b)
{
  b->c=(container_info*)mymalloc(sizeof(container_info));
  memset((void *)b->c, 0, sizeof(container_info));
  b->flags.b_Container = 1;
  if(b->parent != NULL)
  {
    if (b->parent->c->flags.b_IconBack || b->parent->c->flags.b_IconParent)
      b->c->flags.b_IconParent = 1;
    if (b->parent->c->flags.b_Colorset ||
	b->parent->c->flags.b_ColorsetParent)
      b->c->flags.b_ColorsetParent = 1;
  }
  else
  {
    b->c->flags.b_Font = 1;
    b->c->flags.b_Padding = 1;
    b->c->flags.b_Frame = 1;
    b->c->flags.b_Back = 1;
    b->c->flags.b_Fore = 1;
    b->c->font_string=safestrdup("fixed");
    b->c->xpad=2;
    b->c->ypad=4;
    b->c->back=safestrdup("rgb:90/80/90");
    b->c->fore=safestrdup("black");
    b->c->framew=2;
  }

}

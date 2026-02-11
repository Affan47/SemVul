draw_sprprog (const a_sprite *sprite, a_pixel *dest)
{
  a_sprite_prog_list *list;

  assert (sprite->all.kind == S_PROG || sprite->all.kind == S_PROG_WAV);

  for (list = sprite->prog.list; list; list = list->cdr) {
    a_sprite *s = list->car;
    s->draw (s, dest + list->offset);
  }
}

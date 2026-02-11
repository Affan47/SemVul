check_sprite_status_full(int sprite_no)
{

  check_seq_status(spr[sprite_no].pseq);

  if (spr[sprite_no].base_walk > -1)
    check_base(spr[sprite_no].base_walk);
}

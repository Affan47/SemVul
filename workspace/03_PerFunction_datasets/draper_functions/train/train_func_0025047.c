draw_vehicle_tail (int c, a_pixel* dest)
{
  int d;
  const a_pixel *posit = 0;
  int s = DIR8_PAIR(REVERSE_DIR(player[c].old_way),
		    REVERSE_DIR(player[c].way));
  const a_sprite *spr;

  if (player[c].way & 1) {
    d = player[c].d.h.l / 5462;
    spr = trails[s][12 - (d + 12) / 2];
  } else {
    d = player[c].d.h.l / 6554;
    spr = trails[s][10 - (d + 10) / 2];
  }
  draw_sprglenz_custom (spr, dest, glenz[c + 2]);

  posit = vehicles_img.buffer + (c << 6) + (player[c].way << 4);

  if (invincible[c])
    posit += 10 * 320;

  switch (player[c].way) {
  case D_LEFT:
    copy_square_transp (posit + d, dest, (char) d, 0);
    break;
  case D_RIGHT:
    copy_square_transp (posit, dest + d, (char) d, 0);
    break;
  case D_UP:
    copy_square_transp (posit + d * 320, dest, 0, (char) d);
    break;
  case D_DOWN:
    copy_square_transp (posit, dest + d * xbuf, 0, (char) d);
    break;
  }
}

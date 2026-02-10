headerbar_bitmap(unsigned bmap_id, unsigned alignment, void (*f)(void))
{
  unsigned hb_index;

  if ((bx_headerbar_entries+1) > BX_MAX_HEADERBAR_ENTRIES)
    BX_PANIC(("x: too many headerbar entries, increase BX_MAX_HEADERBAR_ENTRIES"));

  bx_headerbar_entries++;
  hb_index = bx_headerbar_entries - 1;

  bx_headerbar_entry[hb_index].bitmap = bx_bitmaps[bmap_id].bmap;
  bx_headerbar_entry[hb_index].xdim   = bx_bitmaps[bmap_id].xdim;
  bx_headerbar_entry[hb_index].ydim   = bx_bitmaps[bmap_id].ydim;
  bx_headerbar_entry[hb_index].alignment = alignment;
  bx_headerbar_entry[hb_index].f = f;
  if (alignment == BX_GRAVITY_LEFT) {
    bx_headerbar_entry[hb_index].xorigin = bx_bitmap_left_xorigin;
    bx_headerbar_entry[hb_index].yorigin = 0;
    bx_bitmap_left_xorigin += bx_bitmaps[bmap_id].xdim;
  }
  else {
    bx_bitmap_right_xorigin += bx_bitmaps[bmap_id].xdim;
    bx_headerbar_entry[hb_index].xorigin = bx_bitmap_right_xorigin;
    bx_headerbar_entry[hb_index].yorigin = 0;
  }
  return(hb_index);
}

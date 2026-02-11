update_left_panel (void)
{
  draw_level_map (xplan, yplan, 0);
  {
    copy_tile (level_map
	       [((xplan + xplandec / 24) & hplaninfo.xwrap) +
		((yplan + yplandec / 20) & hplaninfo.ywrap) *
		hplaninfo.xt].number, hedit_buffer + 293 + 88 * xbuf);
    draw_left_panel (curdallep ());
    rectangle_copy (0, 71, 30, 13, 290, 71, &heditrsc);
    if (level_map[curdallep ()].sprite != 0)
      draw_text ("[S]", 309, 71, 8, 0);
    draw_text (type_name[level_map[curdallep ()].type], 304, 78, 8, 1);
  }
  frame (xplandec, yplandec, 23, 19, 8);
  rectangle_copy (0, 57, 30, 6, 290, 57, &heditrsc);
  sprintf (nombre, "%u", ((xplan + xplandec / 24) & hplaninfo.xwrap));
  draw_text (nombre, 302, 57, 8, 2);
  sprintf (nombre, "%u", ((yplan + yplandec / 20) & hplaninfo.ywrap));
  draw_text (nombre, 307, 57, 8, 0);
  vsynchro (hedit_buffer);
}

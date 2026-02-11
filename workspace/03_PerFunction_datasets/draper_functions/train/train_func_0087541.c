add_box3 ()
{
  if (importflag != 0)
    return;

  add_struct (mark.x, mark.y, mark.x + mark.w, mark.y, 0, 0, 0, 1, curpen);
  add_struct (mark.x, mark.y, mark.x, mark.y + mark.h, 0, 0, 0, 1, curpen);
  add_struct (mark.x, mark.y + mark.h, mark.x + mark.w, mark.y + mark.h, 0, 0,
	      0, 1, curpen);
  add_struct (mark.x + mark.w, mark.y, mark.x + mark.w, mark.y + mark.h, 0, 0,
	      0, 1, curpen);
  add_struct (mark.x + mark.w + 5, mark.y + 8, mark.x + mark.w + 5,
	      mark.y + mark.h + 8, 10, 0, 0, 1, curpen);
  add_struct (mark.x + mark.w + 9, mark.y + mark.h + 5, mark.x + 9,
	      mark.y + mark.h + 5, 10, 0, 0, 1, curpen);
  FreePix ();
  CreatePix ();
  Display_Mol ();
}

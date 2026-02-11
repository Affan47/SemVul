Grid (GtkWidget * mainw)

{
      if (gridtype < 2)
	gridtype ++;
	  else
	gridtype = 0;
  FreePix ();
  CreatePix ();
  Display_Mol ();

  if (importflag != 0)
    pdbrotate (0, 0, 2);
}

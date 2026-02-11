get_index_Cell (aiSlice)
  long  aiSlice;
{
  long  index;


  index = ERROR_INDEX;

  switch (LV_Function) {
    case DPGEN_ROM2:
      __DBG(
        fprintf (stderr, "LV_xl0(%ld) := %ld.\n",
                 aiSlice, getxlbit (LV_xl0, aiSlice));
        fprintf (stderr, "LV_xl1(%ld) := %ld.\n",
                 aiSlice, getxlbit (LV_xl1, aiSlice));
        fflush (stderr);
      )
      index = (getxlbit (LV_xl1, aiSlice) << 1)
            +  getxlbit (LV_xl0, aiSlice);
      break;
    case DPGEN_ROM4:
      index = (getxlbit (LV_xl3, aiSlice) << 3)
            + (getxlbit (LV_xl2, aiSlice) << 2)
            + (getxlbit (LV_xl1, aiSlice) << 1)
            +  getxlbit (LV_xl0, aiSlice);
      break;
  }


  return (index);
}

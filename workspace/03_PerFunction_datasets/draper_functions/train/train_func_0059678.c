write_rtx_next (void)
{
  outf_p f = get_output_file_with_visibility (NULL);
  int i;
  if (!f)
    return;

  oprintf (f, "\n/* Used to implement the RTX_NEXT macro.  */\n");
  oprintf (f, "EXPORTED_CONST unsigned char rtx_next[NUM_RTX_CODE] = {\n");
  for (i = 0; i < NUM_RTX_CODE; i++)
    if (rtx_next_new[i] == -1)
      oprintf (f, "  0,\n");
    else
      oprintf (f,
	       "  RTX_HDR_SIZE + %d * sizeof (rtunion),\n", rtx_next_new[i]);
  oprintf (f, "};\n");
}

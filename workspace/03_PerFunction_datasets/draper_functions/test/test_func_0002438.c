compute_matchdata_lossless(JB2Image *jimg, MatchData *lib)
{
  int i;
  int nshapes = jimg->get_shape_count();
  for (i=0; i<nshapes; i++)
    {
      JB2Shape &jshp = jimg->get_shape(i);
      lib[i].bits = 0;
      lib[i].area = 0;
      lib[i].match = -1;
      if (! jshp.bits) continue;
      if (jshp.userdata & JB2SHAPE_SPECIAL) continue;
      lib[i].bits = jshp.bits;
      lib[i].area = compute_area(jshp.bits);
    }
}

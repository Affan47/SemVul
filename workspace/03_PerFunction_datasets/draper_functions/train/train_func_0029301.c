gap_story_vthumb_g_main_context_iteration(GapStbMainGlobalParams *sgpp)
{
  gboolean old_gva_lock;

  old_gva_lock = sgpp->gva_lock;
  sgpp->gva_lock = TRUE;


  while(g_main_context_iteration(NULL, FALSE));

  sgpp->gva_lock = old_gva_lock;

}

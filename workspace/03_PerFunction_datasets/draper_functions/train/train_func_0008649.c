p_optimized_prefetch_vthumbs_worker (GapStbMainGlobalParams *sgpp)
{
  GapStoryBoard *stb;

  stb = NULL;
  if((sgpp->stb_widgets) && (sgpp->stb))
  {
    stb = gap_story_board_duplicate_distinct_sorted(stb, sgpp->stb);
  }

  if((sgpp->cll_widgets) && (sgpp->cll))
  {
    stb = gap_story_board_duplicate_distinct_sorted(stb, sgpp->cll);
  }

  if(stb == NULL)
  {
    return;
  }


  p_prefetch_vthumbs(sgpp, stb);
  gap_story_free_storyboard(&stb);
}

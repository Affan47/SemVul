greed(int missing_love)
{
  if (missing_love > 0) {
    return 0;
  } else {


    return -((missing_love * MAX_AI_LOVE) / 1000) *
           ((missing_love * MAX_AI_LOVE) / 1000) / 10;
  }
}

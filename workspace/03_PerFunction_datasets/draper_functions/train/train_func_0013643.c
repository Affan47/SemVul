GetCharSetName()
{

  PRInt32 finalsub = mFinalCharLogicalScore - mFinalCharVisualScore;
  if (finalsub >= MIN_FINAL_CHAR_DISTANCE)
    return LOGICAL_HEBREW_NAME;
  if (finalsub <= -(MIN_FINAL_CHAR_DISTANCE))
    return VISUAL_HEBREW_NAME;


  float modelsub = mLogicalProb->GetConfidence() - mVisualProb->GetConfidence();
  if (modelsub > MIN_MODEL_DISTANCE)
    return LOGICAL_HEBREW_NAME;
  if (modelsub < -(MIN_MODEL_DISTANCE))
    return VISUAL_HEBREW_NAME;


  if (finalsub < 0)
    return VISUAL_HEBREW_NAME;


  return LOGICAL_HEBREW_NAME;
}

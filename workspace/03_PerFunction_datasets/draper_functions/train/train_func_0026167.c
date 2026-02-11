lps25hEvaluateSelfTest(float min, float max, float value, char* string)
{
  if (value < min || value > max)
  {
    DEBUG_PRINT("Self test %s [FAIL]. low: %0.2f, high: %0.2f, measured: %0.2f\n",
                string, min, max, value);
    return false;
  }
  return true;
}

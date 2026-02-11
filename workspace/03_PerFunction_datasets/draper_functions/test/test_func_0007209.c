PR_ParseTimeString(
        const char *string,
        PRBool default_to_gmt,
        PRTime *result)
{
  PRExplodedTime tm;
  PRStatus rv;

  rv = PR_ParseTimeStringToExplodedTime(string,
                                        default_to_gmt,
                                        &tm);
  if (rv != PR_SUCCESS)
        return rv;

  *result = PR_ImplodeTime(&tm);

  return PR_SUCCESS;
}

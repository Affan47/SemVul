prompt(void)
{

    if (!he_nestLevel)
        printf("hdfed%s ", he_prompt);
    else
      {
          int i;

          printf("     %s ", he_prompt);
          for (i = he_nestLevel; i; i--)
              putchar(he_nestChar);
          putchar(' ');
      }

}

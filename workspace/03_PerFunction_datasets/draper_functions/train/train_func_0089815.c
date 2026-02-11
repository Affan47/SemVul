filter_resolution_list (Epson_Scanner * s)
{


  if (s->val[OPT_LIMIT_RESOLUTION].w == SANE_TRUE)
  {


    int i;

    int new_size = 0;
    SANE_Bool is_correct_resolution = SANE_FALSE;

    for (i = 1; i <= s->hw->res_list_size; i++)
    {
      SANE_Word res;
      res = s->hw->res_list[i];
      if ((res < 100) || (0 == (res % 300)) || (0 == (res % 400)))
      {

        new_size++;

        s->hw->resolution_list[new_size] = s->hw->res_list[i];


        if (res == s->val[OPT_RESOLUTION].w)
        {
          is_correct_resolution = SANE_TRUE;
        }
      }
    }
    s->hw->resolution_list[0] = new_size;

    if (is_correct_resolution == SANE_FALSE)
    {
      for (i = 1; i <= new_size; i++)
      {
        if (s->val[OPT_RESOLUTION].w < s->hw->resolution_list[i])
        {
          s->val[OPT_RESOLUTION].w = s->hw->resolution_list[i];
          i = new_size + 1;
        }
      }
    }

  }
  else
  {

    s->hw->resolution_list[0] = s->hw->res_list_size;
    memcpy (&(s->hw->resolution_list[1]), s->hw->res_list,
            s->hw->res_list_size * sizeof (SANE_Word));
  }
}

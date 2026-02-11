seista_parse_zmatrix(const gchar *text,
                          GSList *species_list,
                          gdouble scale,
                          struct model_pak *model)
{
gint i, num_tokens;
gchar **buff;
struct core_pak *core;
struct species_pak *species_data;
static gint state=0;


if (g_ascii_strncasecmp("molecule", text, 8) == 0)
  {
  state = 1;
  if (strstr(text, "frac"))
    zmat_fractional_set(model->zmatrix);
  else
    zmat_cartesian_set(model->zmatrix);
  return;
  }

if (g_ascii_strncasecmp("variable", text, 8) == 0)
  {
  state = 2;
  return;
  }

if (g_ascii_strncasecmp("constant", text, 8) == 0)
  {
  state = 3;
  return;
  }

if (g_ascii_strncasecmp("fractional", text, 10) == 0)
  {
  state = 4;
  model->fractional = TRUE;
  return;
  }

if (g_ascii_strncasecmp("cartesian", text, 9) == 0)
  {
  state = 4;
  model->fractional = FALSE;
  return;
  }


switch (state)
  {
  case 1:

    zmat_core_add(text, model->zmatrix);
    break;

  case 2:

    zmat_var_add(text, model->zmatrix);
    break;

  case 3:

    zmat_const_add(text, model->zmatrix);
    break;

  case 4:

    buff = tokenize(text, &num_tokens);
    if (num_tokens > 3)
      {


      if (species_list)
        {
        i = abs((gint) str_to_float(*(buff)) - 1);
        species_data = g_slist_nth_data(species_list, i);

        core = new_core(species_data->label, model);


        if (species_data->number < 0)
          {
          core->ghost = TRUE;
          core->colour[3] = 0.5;
          }
        }
      else
        core = new_core("X", model);

      model->cores = g_slist_prepend(model->cores, core);

      core->x[0] = scale * str_to_float(*(buff+1));
      core->x[1] = scale * str_to_float(*(buff+2));
      core->x[2] = scale * str_to_float(*(buff+3));
      }
    g_strfreev(buff);
    break;
  }
}

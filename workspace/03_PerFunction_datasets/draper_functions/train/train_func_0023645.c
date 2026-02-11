filter_edited(const QString text)
{
  int i, cnt, n, len;

  char filter_str[32];

  struct annotationblock *annot;


  annot = mainwindow->annotationlist[file_num];

  cnt = edfplus_annotation_count(&annot);

  if(cnt < 1)
  {
    return;
  }

  if(text.length() < 1)
  {
    while(annot != NULL)
    {
      if(!(((annot->ident & (1 << ANNOT_ID_NK_TRIGGER)) && hide_nk_triggers) || ((annot->ident & (1 << ANNOT_ID_BS_TRIGGER)) && hide_bs_triggers)))
      {
        annot->hided_in_list = 0;

        annot->hided = 0;
      }

      annot = annot->next_annotation;
    }

    updateList();

    mainwindow->maincurve->update();

    return;
  }

  strcpy(filter_str, lineedit1->text().toUtf8().data());

  len = strlen(filter_str);

  if(invert_filter == 0)
  {
    while(annot != NULL)
    {
      if(!(((annot->ident & (1 << ANNOT_ID_NK_TRIGGER)) && hide_nk_triggers) || ((annot->ident & (1 << ANNOT_ID_BS_TRIGGER)) && hide_bs_triggers)))
      {
        annot->hided_in_list = 1;

        n = strlen(annot->annotation) - len + 1;

        for(i=0; i<n; i++)
        {
          if(!(strncmp(filter_str, annot->annotation + i, len)))
          {
            annot->hided_in_list = 0;

            annot->hided = 0;

            break;
          }
        }
      }

      annot = annot->next_annotation;
    }
  }
  else
  {
    while(annot != NULL)
    {
      if(!(((annot->ident & (1 << ANNOT_ID_NK_TRIGGER)) && hide_nk_triggers) || ((annot->ident & (1 << ANNOT_ID_BS_TRIGGER)) && hide_bs_triggers)))
      {
        annot->hided_in_list = 0;

        n = strlen(annot->annotation) - len + 1;

        for(i=0; i<n; i++)
        {
          if(!(strncmp(filter_str, annot->annotation + i, len)))
          {
            annot->hided_in_list = 1;

            annot->hided = 1;

            break;
          }
        }
      }

      annot = annot->next_annotation;
    }
  }

  updateList();

  mainwindow->maincurve->update();
}

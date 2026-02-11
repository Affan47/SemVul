arglist_parser_alloc (message_list_ty *mlp, const struct callshapes *shapes)
{
  if (shapes == NULL || shapes->nshapes == 0)
    {
      struct arglist_parser *ap =
        (struct arglist_parser *)
        xmalloc (offsetof (struct arglist_parser, alternative[0]));

      ap->mlp = mlp;
      ap->keyword = NULL;
      ap->keyword_len = 0;
      ap->nalternatives = 0;

      return ap;
    }
  else
    {
      struct arglist_parser *ap =
        (struct arglist_parser *)
        xmalloc (xsum (sizeof (struct arglist_parser),
                       xtimes (shapes->nshapes - 1,
                               sizeof (struct partial_call))));
      size_t i;

      ap->mlp = mlp;
      ap->keyword = shapes->keyword;
      ap->keyword_len = shapes->keyword_len;
      ap->nalternatives = shapes->nshapes;
      for (i = 0; i < shapes->nshapes; i++)
        {
          ap->alternative[i].argnumc = shapes->shapes[i].argnumc;
          ap->alternative[i].argnum1 = shapes->shapes[i].argnum1;
          ap->alternative[i].argnum2 = shapes->shapes[i].argnum2;
          ap->alternative[i].argnum1_glib_context =
            shapes->shapes[i].argnum1_glib_context;
          ap->alternative[i].argnum2_glib_context =
            shapes->shapes[i].argnum2_glib_context;
          ap->alternative[i].argtotal = shapes->shapes[i].argtotal;
          ap->alternative[i].xcomments = shapes->shapes[i].xcomments;
          ap->alternative[i].msgctxt = NULL;
          ap->alternative[i].msgctxt_pos.file_name = NULL;
          ap->alternative[i].msgctxt_pos.line_number = (size_t)(-1);
          ap->alternative[i].msgid = NULL;
          ap->alternative[i].msgid_context = null_context;
          ap->alternative[i].msgid_pos.file_name = NULL;
          ap->alternative[i].msgid_pos.line_number = (size_t)(-1);
          ap->alternative[i].msgid_comment = NULL;
          ap->alternative[i].msgid_plural = NULL;
          ap->alternative[i].msgid_plural_context = null_context;
          ap->alternative[i].msgid_plural_pos.file_name = NULL;
          ap->alternative[i].msgid_plural_pos.line_number = (size_t)(-1);
        }

      return ap;
    }
}

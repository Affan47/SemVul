extract_parenthesized (message_list_ty *mlp,
                       flag_context_ty outer_context,
                       flag_context_list_iterator_ty context_iter,
                       struct arglist_parser *argparser)
{

  int arg = 1;

  int state;

  const struct callshapes *next_shapes = NULL;

  flag_context_list_iterator_ty next_context_iter =
    passthrough_context_list_iterator;


  flag_context_list_iterator_ty selectorcall_context_iter =
    passthrough_context_list_iterator;

  flag_context_ty inner_context =
    inherited_context (outer_context,
                       flag_context_list_iterator_advance (&context_iter));


  state = 0;

  for (;;)
    {
      xgettext_token_ty token;

      x_c_lex (&token);
      switch (token.type)
        {
        case xgettext_token_type_keyword:
          next_shapes = token.shapes;
          state = 1;
          goto keyword_or_symbol;

        case xgettext_token_type_symbol:
          state = 0;
        keyword_or_symbol:
          next_context_iter =
            flag_context_list_iterator (
              flag_context_list_table_lookup (
                flag_context_list_table,
                token.string, strlen (token.string)));
          if (objc_extensions)
            {
              size_t token_string_len = strlen (token.string);
              token.string = xrealloc (token.string, token_string_len + 2);
              token.string[token_string_len] = ':';
              token.string[token_string_len + 1] = '\0';
              selectorcall_context_iter =
                flag_context_list_iterator (
                  flag_context_list_table_lookup (
                    flag_context_list_table,
                    token.string, token_string_len + 1));
            }
          free (token.string);
          continue;

        case xgettext_token_type_lparen:
          if (extract_parenthesized (mlp, inner_context, next_context_iter,
                                     arglist_parser_alloc (mlp,
                                                           state ? next_shapes : NULL)))
            {
              arglist_parser_done (argparser, arg);
              return true;
            }
          next_context_iter = null_context_list_iterator;
          selectorcall_context_iter = null_context_list_iterator;
          state = 0;
          continue;

        case xgettext_token_type_rparen:
          arglist_parser_done (argparser, arg);
          return false;

        case xgettext_token_type_comma:
          arg++;
          inner_context =
            inherited_context (outer_context,
                               flag_context_list_iterator_advance (
                                 &context_iter));
          next_context_iter = passthrough_context_list_iterator;
          selectorcall_context_iter = passthrough_context_list_iterator;
          state = 0;
          continue;

        case xgettext_token_type_colon:
          if (objc_extensions)
            {
              context_iter = selectorcall_context_iter;
              inner_context =
                inherited_context (inner_context,
                                   flag_context_list_iterator_advance (
                                     &context_iter));
              next_context_iter = passthrough_context_list_iterator;
              selectorcall_context_iter = passthrough_context_list_iterator;
            }
          else
            {
              next_context_iter = null_context_list_iterator;
              selectorcall_context_iter = null_context_list_iterator;
            }
          state = 0;
          continue;

        case xgettext_token_type_string_literal:
          if (extract_all)
            remember_a_message (mlp, NULL, token.string, inner_context,
                                &token.pos, NULL, token.comment);
          else
            arglist_parser_remember (argparser, arg, token.string,
                                     inner_context,
                                     token.pos.file_name, token.pos.line_number,
                                     token.comment);
          drop_reference (token.comment);
          next_context_iter = null_context_list_iterator;
          selectorcall_context_iter = null_context_list_iterator;
          state = 0;
          continue;

        case xgettext_token_type_other:
          next_context_iter = null_context_list_iterator;
          selectorcall_context_iter = null_context_list_iterator;
          state = 0;
          continue;

        case xgettext_token_type_eof:
          arglist_parser_done (argparser, arg);
          return true;

        default:
          abort ();
        }
    }
}

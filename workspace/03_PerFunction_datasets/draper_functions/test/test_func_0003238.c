read_track_kerns (AFMHandle handle, ParseCtx *ctx, AFMFont font)
{
  int i;
  AFMNode node;
  AFMTrackKern *tk;
  AFMKey key;

  for (i = 0; i < font->num_kern_pairs; i++)
    {
      tk = &font->track_kerns[i];
      get_key (handle, ctx, &key);


      if (key != kTrackKern)
	parse_error (handle, AFM_ERROR_SYNTAX);

      GET_VALUE (AFM_TYPE_INTEGER);
      tk->degree = node.u.integer;

      GET_VALUE (AFM_TYPE_NUMBER);
      tk->min_ptsize = node.u.number;

      GET_VALUE (AFM_TYPE_NUMBER);
      tk->min_kern = node.u.number;

      GET_VALUE (AFM_TYPE_NUMBER);
      tk->max_ptsize = node.u.number;

      GET_VALUE (AFM_TYPE_NUMBER);
      tk->max_kern = node.u.number;
    }


  get_key (handle, ctx, &key);
  if (key != kEndTrackKern)
    parse_error (handle, AFM_ERROR_SYNTAX);
}

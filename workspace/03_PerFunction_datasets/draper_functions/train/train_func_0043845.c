end_stream (CutStreamParser *parser, CutStreamParserPrivate *priv,
            GMarkupParseContext *context,
            const gchar *element_name, GError **error)
{
    if (priv->run_context)
        cut_run_context_emit_complete_run(priv->run_context,
                                          priv->stream_success);
}

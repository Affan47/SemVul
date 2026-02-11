json_parser_has_assignment (JsonParser  *parser,
                            gchar      **variable_name)
{
  JsonParserPrivate *priv;

  g_return_val_if_fail (JSON_IS_PARSER (parser), FALSE);

  priv = parser->priv;

  if (priv->has_assignment && variable_name)
    *variable_name = priv->variable_name;

  return priv->has_assignment;
}

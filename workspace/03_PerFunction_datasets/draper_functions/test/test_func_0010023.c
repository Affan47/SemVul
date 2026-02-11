jsparser_new()
{
    jsparser_ctx *js;

    js = CAST(jsparser_ctx *, calloc(1, sizeof(jsparser_ctx)));
    if (js == NULL)
      return NULL;

    js->statemachine_def = create_statemachine_definition();
    if (js->statemachine_def == NULL)
      return NULL;

    js->statemachine = statemachine_new(js->statemachine_def, js);
    if (js->statemachine == NULL)
      return NULL;

    jsparser_reset(js);

    return js;
}

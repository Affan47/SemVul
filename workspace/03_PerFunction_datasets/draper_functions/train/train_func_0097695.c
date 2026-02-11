script_wrapper_stream_free(GtNodeStream *ns)
{
  GtScriptWrapperStream *script_wrapper_stream;
  if (!ns) return;
  script_wrapper_stream = script_wrapper_stream_cast(ns);
  if (script_wrapper_stream->free_func)
    script_wrapper_stream->free_func(NULL);
}

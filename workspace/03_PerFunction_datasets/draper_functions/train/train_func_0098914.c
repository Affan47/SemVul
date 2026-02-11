in_process_proc (void *cls,
		 const char *plugin_name,
		 enum EXTRACTOR_MetaType type,
		 enum EXTRACTOR_MetaFormat format,
		 const char *data_mime_type,
		 const char *data,
		 size_t data_len)
{
  struct InProcessContext *ctx = cls;
  int ret;

  if (0 != ctx->finished)
    return 1;
  ret = ctx->proc (ctx->proc_cls,
		   plugin_name,
		   type,
		   format,
		   data_mime_type,
		   data,
		   data_len);
  if (0 != ret)
    ctx->finished = 1;
  return ret;
}

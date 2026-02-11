JP2StreamManager(Image *image)
{
  jas_stream_t
    *stream;

  StreamManager
    *source;

  stream=MagickAllocateMemory(jas_stream_t *,sizeof(jas_stream_t));
  if (stream == (jas_stream_t *) NULL)
    return((jas_stream_t *) NULL);
  (void) memset(stream,0,sizeof(jas_stream_t));
  stream->rwlimit_=(-1);
  stream->obj_=MagickAllocateMemory(jas_stream_obj_t *,sizeof(StreamManager));
  if (stream->obj_ == (jas_stream_obj_t *) NULL)
    return((jas_stream_t *) NULL);
  stream->ops_=(&StreamOperators);
  stream->openmode_=JAS_STREAM_READ | JAS_STREAM_WRITE | JAS_STREAM_BINARY;
  stream->bufbase_=stream->tinybuf_;
  stream->bufsize_=1;
  stream->bufstart_=(&stream->bufbase_[JAS_STREAM_MAXPUTBACK]);
  stream->ptr_=stream->bufstart_;
  stream->bufmode_|=JAS_STREAM_UNBUF & JAS_STREAM_BUFMODEMASK;
  source=(StreamManager *) stream->obj_;
  source->image=image;
  return(stream);
}

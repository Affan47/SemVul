FlushLexerBuffer() {
#ifdef YY_FLUSH_BUFFER
  YY_FLUSH_BUFFER;
#else
  yy_flush_buffer(YY_CURRENT_BUFFER );
#endif
}

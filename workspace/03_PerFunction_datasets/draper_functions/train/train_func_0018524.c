trace_screen_context_create(struct pipe_screen *_screen, void *priv)
{
   struct trace_screen *tr_scr = trace_screen(_screen);
   struct pipe_screen *screen = tr_scr->screen;
   struct pipe_context *result;

   trace_dump_call_begin("pipe_screen", "context_create");

   trace_dump_arg(ptr, screen);

   result = screen->context_create(screen, priv);

   trace_dump_ret(ptr, result);

   trace_dump_call_end();

   result = trace_context_create(tr_scr, result);

   return result;
}

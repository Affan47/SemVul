trace_dump_blend_color(const struct pipe_blend_color *state)
{
   if (!trace_dumping_enabled_locked())
      return;

   if(!state) {
      trace_dump_null();
      return;
   }

   trace_dump_struct_begin("pipe_blend_color");

   trace_dump_member_array(float, state, color);

   trace_dump_struct_end();
}

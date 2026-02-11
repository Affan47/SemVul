util_dump_draw_info(FILE *stream, const struct pipe_draw_info *state)
{
   if(!state) {
      util_dump_null(stream);
      return;
   }

   util_dump_struct_begin(stream, "pipe_draw_info");

   util_dump_member(stream, bool, state, indexed);

   util_dump_member(stream, uint, state, mode);
   util_dump_member(stream, uint, state, start);
   util_dump_member(stream, uint, state, count);

   util_dump_member(stream, uint, state, start_instance);
   util_dump_member(stream, uint, state, instance_count);

   util_dump_member(stream, int,  state, index_bias);
   util_dump_member(stream, uint, state, min_index);
   util_dump_member(stream, uint, state, max_index);

   util_dump_member(stream, bool, state, primitive_restart);
   util_dump_member(stream, uint, state, restart_index);

   util_dump_member(stream, ptr, state, count_from_stream_output);

   util_dump_struct_end(stream);
}

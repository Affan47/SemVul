util_dump_transfer(FILE *stream, const struct pipe_transfer *state)
{
   if(!state) {
      util_dump_null(stream);
      return;
   }

   util_dump_struct_begin(stream, "pipe_transfer");

   util_dump_member(stream, ptr, state, resource);
   util_dump_member(stream, uint, state, level);
   util_dump_member(stream, uint, state, usage);
   util_dump_member_begin(stream, "box");
   util_dump_box(stream, &state->box);
   util_dump_member_end(stream);
   util_dump_member(stream, uint, state, stride);
   util_dump_member(stream, uint, state, layer_stride);

   util_dump_struct_end(stream);
}

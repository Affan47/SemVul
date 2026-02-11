util_dump_poly_stipple(FILE *stream, const struct pipe_poly_stipple *state)
{
   if(!state) {
      util_dump_null(stream);
      return;
   }

   util_dump_struct_begin(stream, "pipe_poly_stipple");

   util_dump_member_begin(stream, "stipple");
   util_dump_member_array(stream, uint, state, stipple);
   util_dump_member_end(stream);

   util_dump_struct_end(stream);
}

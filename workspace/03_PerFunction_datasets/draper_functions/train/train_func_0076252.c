is_color_fast_clear_compatible(struct brw_context *brw,
                               mesa_format format,
                               const union gl_color_union *color)
{
   if (_mesa_is_format_integer_color(format))
      return false;

   for (int i = 0; i < 4; i++) {
      if (color->f[i] != 0.0 && color->f[i] != 1.0) {
         perf_debug("Clear color unsupported by fast color clear.  "
                    "Falling back to slow clear.\n");
         return false;
      }
   }
   return true;
}

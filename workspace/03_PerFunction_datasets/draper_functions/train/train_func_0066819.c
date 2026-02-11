find_supported_format(struct pipe_screen *screen,
                      const enum pipe_format formats[],
                      enum pipe_texture_target target,
                      unsigned sample_count,
                      unsigned tex_usage,
                      boolean allow_dxt)
{
   uint i;
   for (i = 0; formats[i]; i++) {
      if (screen->is_format_supported(screen, formats[i], target,
                                      sample_count, tex_usage)) {
         if (!allow_dxt && util_format_is_s3tc(formats[i])) {

            continue;
         }

         return formats[i];
      }
   }
   return PIPE_FORMAT_NONE;
}

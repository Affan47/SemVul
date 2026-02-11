ctpl_check_version (guint major,
                    guint minor,
                    guint micro)
{
  return (ctpl_major_version > major ||
          (ctpl_major_version == major && \
           (ctpl_minor_version > minor || \
            (ctpl_minor_version == minor && ctpl_micro_version >= micro))));
}

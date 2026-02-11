gst_visual_actor_plugin_is_gl (VisObject * plugin, const gchar * name)
{
  gboolean is_gl;
  gint depth;

#if !defined(VISUAL_API_VERSION)

  depth = VISUAL_PLUGIN_ACTOR (plugin)->depth;
  is_gl = (depth == VISUAL_VIDEO_DEPTH_GL);

#elif VISUAL_API_VERSION >= 4000 && VISUAL_API_VERSION < 5000

  depth = VISUAL_ACTOR_PLUGIN (plugin)->vidoptions.depth;

  is_gl = (depth & VISUAL_VIDEO_DEPTH_GL) == VISUAL_VIDEO_DEPTH_GL;

#else
# error what libvisual version is this?
#endif

  if (!is_gl) {
    GST_DEBUG ("plugin %s is not a GL plugin (%d), registering", name, depth);
  } else {
    GST_DEBUG ("plugin %s is a GL plugin (%d), ignoring", name, depth);
  }

  return is_gl;
}

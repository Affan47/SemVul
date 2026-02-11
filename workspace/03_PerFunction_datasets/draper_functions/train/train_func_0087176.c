gst_synae_scope_init (GstSynaeScope * scope, GstSynaeScopeClass * g_class)
{
  guint32 *colors = scope->colors;
  guint *shade = scope->shade;
  guint i, r, g, b;

#define BOUND(x) ((x) > 255 ? 255 : (x))
#define PEAKIFY(x) BOUND((x) - (x)*(255-(x))/255/2)

  for (i = 0; i < 256; i++) {
    r = PEAKIFY ((i & 15 * 16));
    g = PEAKIFY ((i & 15) * 16 + (i & 15 * 16) / 4);
    b = PEAKIFY ((i & 15) * 16);

    colors[i] = (r << 16) | (g << 8) | b;
  }
#undef BOUND
#undef PEAKIFY

  for (i = 0; i < 256; i++)
    shade[i] = i * 200 >> 8;
}

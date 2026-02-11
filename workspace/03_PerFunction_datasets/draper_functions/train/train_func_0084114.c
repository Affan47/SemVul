get_property (GObject    *object,
              guint       prop_id,
              GValue     *value,
              GParamSpec *pspec)
{
  GeglSamplerCubic *self = GEGL_SAMPLER_CUBIC (object);

  switch (prop_id)
    {
      case PROP_B:
        g_value_set_double (value, self->b);
        break;

      case PROP_TYPE:
        g_value_set_string (value, self->type);
        break;

      default:
        break;
    }
}

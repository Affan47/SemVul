propertiesRemoveSurf(gpointer key _U_, gpointer value, gpointer data)
{
  guint idSurf, i;
  VisuSurfacesProperties *prop;

  idSurf = GPOINTER_TO_INT(data);
  prop = (VisuSurfacesProperties*)value;

  switch (prop->type)
    {
    case G_TYPE_FLOAT:
      for (i = idSurf; i < prop->surf->nsurf; i++)
	((float*)prop->data)[i] = ((float*)prop->data)[i + 1];
      prop->data = g_realloc(prop->data, prop->surf->nsurf * sizeof(float));
      break;
    default:
      g_warning("Unimplemented format.");
    }
}

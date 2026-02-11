tool_shade_newFromData(const gchar* labelUTF8, guint len, float *vectCh1,
                                  float *vectCh2, float *vectCh3, ToolShadeColorMode colorMode)
{
  ToolShade *shade;
  guint i;

  g_return_val_if_fail(labelUTF8 && vectCh1 && vectCh2 && vectCh3 &&
		       colorMode < TOOL_SHADE_COLOR_MODE_N_VALUES && len > 0, (ToolShade*)0);

  DBG_fprintf(stderr, "Tool ToolShade: create a new ToolShade object (array):");
  shade = g_malloc(sizeof(ToolShade));
  shade->labelUTF8 = g_strdup(labelUTF8);
  shade->colorMode = colorMode;
  shade->mode      = TOOL_SHADE_MODE_ARRAY;
  shade->nVals     = len;
  shade->index     = g_malloc(sizeof(float) * len);
  shade->vectCh[0] = g_malloc(sizeof(float) * len);
  shade->vectCh[1] = g_malloc(sizeof(float) * len);
  shade->vectCh[2] = g_malloc(sizeof(float) * len);
  for (i = 0; i < len; i++)
    shade->index[i] = (float)i / (float)(len - 1);
  memcpy(shade->vectCh[0], vectCh1, sizeof(float) * len);
  memcpy(shade->vectCh[1], vectCh2, sizeof(float) * len);
  memcpy(shade->vectCh[2], vectCh3, sizeof(float) * len);
  shade->userDefined = TRUE;
  shade->steps     = (gchar*)0;

  DBG_fprintf(stderr, " %p.\n", (gpointer)shade);
  return shade;
}

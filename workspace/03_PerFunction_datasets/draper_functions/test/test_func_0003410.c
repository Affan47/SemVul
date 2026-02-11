evas_software_xlib_x_color_allocate(Display         *disp,
                                    Colormap         cmap,
                                    Visual          *vis,
                                    Convert_Pal_Mode colors)
{
   Convert_Pal_Priv *palpriv;
   Convert_Pal      *pal;
   Convert_Pal_Mode  c;
   Eina_List        *l;


   EINA_LIST_FOREACH(palettes, l, pal)
     {
	palpriv = pal->data;
	if ((disp == palpriv->disp) &&
	    (vis == palpriv->vis) &&
	    (cmap == palpriv->cmap))
	  {
	     pal->references++;
	     return pal;
	  }
     }
   pal = calloc(1, sizeof(struct _Convert_Pal));
   if (!pal) return NULL;
   for (c = colors; c > PAL_MODE_NONE; c--)
     {
	if (x_color_alloc[c])
	  {

	     pal->lookup = (x_color_alloc[c])(disp, cmap, vis);
	     if (pal->lookup) break;
	  }
     }
   pal->references = 1;
   pal->colors = c;
   pal->count = x_color_count[c];
   palpriv = calloc(1, sizeof(Convert_Pal_Priv));
   pal->data = palpriv;
   if (!palpriv)
     {
	if (pal->lookup) free(pal->lookup);
	free(pal);
	return NULL;
     }
   palpriv->disp = disp;
   palpriv->vis = vis;
   palpriv->cmap = cmap;
   if (pal->colors == PAL_MODE_NONE)
     {
	if (pal->lookup) free(pal->lookup);
	free(pal);
	return NULL;
     }
   palettes = eina_list_append(palettes, pal);
   return pal;
}

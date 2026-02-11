evas_gl_surface_create(Evas_GL *evas_gl, Evas_GL_Config *config, int width, int height)
{
   Evas_GL_Surface *surf;

   MAGIC_CHECK(evas_gl, Evas_GL, MAGIC_EVAS_GL);
   return NULL;
   MAGIC_CHECK_END();

   if (!config)
     {
        ERR("Invalid Config Pointer!");
        return NULL;
     }

   if ( (width <= 0) || (height <= 0))
     {
        ERR("Invalid surface dimensions: %d, %d", width, height);
        return NULL;
     }

   surf = calloc(1, sizeof(Evas_GL_Surface));

   if (!surf) return NULL;

   surf->data = evas_gl->evas->engine.func->gl_surface_create(evas_gl->evas->engine.data.output, config, width, height);

   if (!surf->data)
     {
        ERR("Failed creating a surface from the engine.");
        free(surf);
        return NULL;
     }


   evas_gl->surfaces = eina_list_prepend(evas_gl->surfaces, surf);

   return surf;
}

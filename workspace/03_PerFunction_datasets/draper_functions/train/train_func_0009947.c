pt_unref(Evas_GL_Texture_Pool *pt)
{
   if (!pt) return;
   if (!pt->gc) return;
   pt->references--;
   if (pt->references != 0) return;

   if (!((pt->render) || (pt->native)))
     {
        if (pt->whole)
           pt->gc->shared->tex.whole =
           eina_list_remove(pt->gc->shared->tex.whole, pt);
        else
           pt->gc->shared->tex.atlas [pt->slot][pt->fslot] =
           eina_list_remove(pt->gc->shared->tex.atlas[pt->slot][pt->fslot], pt);
     }
   evas_gl_texture_pool_empty(pt);
   free(pt);
}

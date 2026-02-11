dialog_constrain(gint32 image_id, gint32 drawable_id,
                             gpointer data)
{
   if(drawable_id == -1) return(1);
   if(gimp_drawable_is_gray(drawable_id))
   {
      *(int*)data += 1;
      return(1);
   }
   return(0);
}

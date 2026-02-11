p_save_as_tmp_png_file(const char *filename, gint32 image_id, gint32 drawable_id
   , gint32 png_interlaced, gint32 png_compression)
{
   static char     *l_called_proc = "file-png-save2";
   GimpParam          *return_vals;
   int              nreturn_vals;

   if(gap_debug)
   {
     printf("GAP: PNG encode via call of %s on filename: %s, image_id:%d, drawable_id:%d %s\n"
            , l_called_proc
            , filename
            , image_id
            , drawable_id
            );
   }

   return_vals = gimp_run_procedure (l_called_proc,
                                 &nreturn_vals,
                                 GIMP_PDB_INT32,     GIMP_RUN_NONINTERACTIVE ,
                                 GIMP_PDB_IMAGE,     image_id,
                                 GIMP_PDB_DRAWABLE,  drawable_id,
                                 GIMP_PDB_STRING,    filename,
                                 GIMP_PDB_STRING,    filename,
                                 GIMP_PDB_INT32,     png_interlaced,
                                 GIMP_PDB_INT32,     png_compression,
                                 GIMP_PDB_INT32,     0,
                                 GIMP_PDB_INT32,     0,
                                 GIMP_PDB_INT32,     0,
                                 GIMP_PDB_INT32,     0,
                                 GIMP_PDB_INT32,     0,
                                 GIMP_PDB_INT32,     0,
                                 GIMP_PDB_INT32,     0,
                                 GIMP_PDB_END);

   if (return_vals[0].data.d_status == GIMP_PDB_SUCCESS)
   {
      gimp_destroy_params(return_vals, nreturn_vals);
      return (TRUE);
   }

   gimp_destroy_params(return_vals, nreturn_vals);
   printf("GAP: Error: PDB call of %s failed on filename: %s, image_id:%d, drawable_id:%d, d_status:%d %s\n"
          , l_called_proc
          , filename
          , image_id
          , drawable_id
          , (int)return_vals[0].data.d_status
          , p_status_to_string(return_vals[0].data.d_status)
          );
   return(FALSE);

}

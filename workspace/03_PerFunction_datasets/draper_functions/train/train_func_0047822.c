emit_wpos(struct st_context *st,
          struct st_translate *t,
          const struct gl_program *program,
          struct ureg_program *ureg)
{
   const struct gl_fragment_program *fp =
      (const struct gl_fragment_program *) program;
   struct pipe_screen *pscreen = st->pipe->screen;
   GLfloat adjX = 0.0f;
   GLfloat adjY[2] = { 0.0f, 0.0f };
   boolean invert = FALSE;


   if (fp->OriginUpperLeft) {

      if (pscreen->get_param(pscreen, PIPE_CAP_TGSI_FS_COORD_ORIGIN_UPPER_LEFT)) {

      }
      else if (pscreen->get_param(pscreen, PIPE_CAP_TGSI_FS_COORD_ORIGIN_LOWER_LEFT)) {

         ureg_property_fs_coord_origin(ureg, TGSI_FS_COORD_ORIGIN_LOWER_LEFT);
         invert = TRUE;
      }
      else
         assert(0);
   }
   else {

      if (pscreen->get_param(pscreen, PIPE_CAP_TGSI_FS_COORD_ORIGIN_LOWER_LEFT))

         ureg_property_fs_coord_origin(ureg, TGSI_FS_COORD_ORIGIN_LOWER_LEFT);
      else if (pscreen->get_param(pscreen, PIPE_CAP_TGSI_FS_COORD_ORIGIN_UPPER_LEFT))

         invert = TRUE;
      else
         assert(0);
   }

   if (fp->PixelCenterInteger) {

      if (pscreen->get_param(pscreen, PIPE_CAP_TGSI_FS_COORD_PIXEL_CENTER_INTEGER)) {

         adjY[1] = 1.0f;
         ureg_property_fs_coord_pixel_center(ureg, TGSI_FS_COORD_PIXEL_CENTER_INTEGER);
      }
      else if (pscreen->get_param(pscreen, PIPE_CAP_TGSI_FS_COORD_PIXEL_CENTER_HALF_INTEGER)) {

         adjX = -0.5f;
         adjY[0] = -0.5f;
         adjY[1] = 0.5f;
      }
      else
         assert(0);
   }
   else {

      if (pscreen->get_param(pscreen, PIPE_CAP_TGSI_FS_COORD_PIXEL_CENTER_HALF_INTEGER)) {

      }
      else if (pscreen->get_param(pscreen, PIPE_CAP_TGSI_FS_COORD_PIXEL_CENTER_INTEGER)) {

         adjX = adjY[0] = adjY[1] = 0.5f;
         ureg_property_fs_coord_pixel_center(ureg, TGSI_FS_COORD_PIXEL_CENTER_INTEGER);
      }
      else
         assert(0);
   }


   emit_wpos_adjustment(t, program, invert, adjX, adjY);
}

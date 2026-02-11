compute_row_addresses( OSMesaContext osmesa )
{
   GLint bytesPerRow, i;
   GLubyte *origin = (GLubyte *) osmesa->srb->Buffer;
   GLint rowlength;
   GLint height = osmesa->srb->Base.Height;

   if (osmesa->userRowLength)
      rowlength = osmesa->userRowLength;
   else
      rowlength = osmesa->srb->Base.Width;

   bytesPerRow = rowlength * _mesa_get_format_bytes(osmesa->srb->Base.Format);

   if (osmesa->yup) {

      for (i = 0; i < height; i++) {
         osmesa->rowaddr[i] = (GLvoid *) ((GLubyte *) origin + i * bytesPerRow);
      }
   }
   else {

      for (i = 0; i < height; i++) {
         GLint j = height - i - 1;
         osmesa->rowaddr[i] = (GLvoid *) ((GLubyte *) origin + j * bytesPerRow);
      }
   }
}

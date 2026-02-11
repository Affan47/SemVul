_mesa_pack_uint_z_row(mesa_format format, GLuint n,
                      const GLuint *src, void *dst)
{
   switch (format) {
   case MESA_FORMAT_S8_UINT_Z24_UNORM:
   case MESA_FORMAT_X8Z24_UNORM:
      {

         GLuint *d = ((GLuint *) dst);
         GLuint i;
         for (i = 0; i < n; i++) {
            GLuint s = d[i] & 0xff;
            GLuint z = src[i] & 0xffffff00;
            d[i] = z | s;
         }
      }
      break;
   case MESA_FORMAT_Z24_UNORM_S8_UINT:
   case MESA_FORMAT_Z24_UNORM_X8_UINT:
      {

         GLuint *d = ((GLuint *) dst);
         GLuint i;
         for (i = 0; i < n; i++) {
            GLuint s = d[i] & 0xff000000;
            GLuint z = src[i] >> 8;
            d[i] = s | z;
         }
      }
      break;
   case MESA_FORMAT_Z_UNORM16:
      {
         GLushort *d = ((GLushort *) dst);
         GLuint i;
         for (i = 0; i < n; i++) {
            d[i] = src[i] >> 16;
         }
      }
      break;
   case MESA_FORMAT_Z_UNORM32:
      memcpy(dst, src, n * sizeof(GLfloat));
      break;
   case MESA_FORMAT_Z_FLOAT32:
      {
         GLuint *d = ((GLuint *) dst);
         const GLdouble scale = 1.0 / (GLdouble) 0xffffffff;
         GLuint i;
         for (i = 0; i < n; i++) {
            d[i] = (GLuint) (src[i] * scale);
            assert(d[i] >= 0.0f);
            assert(d[i] <= 1.0f);
         }
      }
      break;
   case MESA_FORMAT_Z32_FLOAT_S8X24_UINT:
      {
         struct z32f_x24s8 *d = (struct z32f_x24s8 *) dst;
         const GLdouble scale = 1.0 / (GLdouble) 0xffffffff;
         GLuint i;
         for (i = 0; i < n; i++) {
            d[i].z = (GLfloat) (src[i] * scale);
            assert(d[i].z >= 0.0f);
            assert(d[i].z <= 1.0f);
         }
      }
      break;
   default:
      _mesa_problem(NULL, "unexpected format in _mesa_pack_uint_z_row()");
   }
}

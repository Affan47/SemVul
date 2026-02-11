_mesa_Materialiv(GLenum face, GLenum pname, const GLint *params )
{
   GLfloat fparam[4];
   switch (pname) {
   case GL_AMBIENT:
   case GL_DIFFUSE:
   case GL_SPECULAR:
   case GL_EMISSION:
   case GL_AMBIENT_AND_DIFFUSE:
      fparam[0] = INT_TO_FLOAT( params[0] );
      fparam[1] = INT_TO_FLOAT( params[1] );
      fparam[2] = INT_TO_FLOAT( params[2] );
      fparam[3] = INT_TO_FLOAT( params[3] );
      break;
   case GL_SHININESS:
      fparam[0] = (GLfloat) params[0];
      break;
   case GL_COLOR_INDEXES:
      fparam[0] = (GLfloat) params[0];
      fparam[1] = (GLfloat) params[1];
      fparam[2] = (GLfloat) params[2];
      break;
   default:
      ;
   }
   MATERIALFV(face, pname, fparam);
}

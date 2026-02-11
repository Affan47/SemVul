init_light( struct gl_light *l, GLuint n )
{
   make_empty_list( l );

   ASSIGN_4V( l->Ambient, 0.0, 0.0, 0.0, 1.0 );
   if (n==0) {
      ASSIGN_4V( l->Diffuse, 1.0, 1.0, 1.0, 1.0 );
      ASSIGN_4V( l->Specular, 1.0, 1.0, 1.0, 1.0 );
   }
   else {
      ASSIGN_4V( l->Diffuse, 0.0, 0.0, 0.0, 1.0 );
      ASSIGN_4V( l->Specular, 0.0, 0.0, 0.0, 1.0 );
   }
   ASSIGN_4V( l->EyePosition, 0.0, 0.0, 1.0, 0.0 );
   ASSIGN_3V( l->SpotDirection, 0.0, 0.0, -1.0 );
   l->SpotExponent = 0.0;
   l->SpotCutoff = 180.0;
   l->_CosCutoff = 0.0;
   l->ConstantAttenuation = 1.0;
   l->LinearAttenuation = 0.0;
   l->QuadraticAttenuation = 0.0;
   l->Enabled = GL_FALSE;
}

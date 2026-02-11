_dxf_SET_MATERIAL_SPECULAR (void *ctx,
					float r, float g, float b, float power)
{


  float color[4] ;

  ENTRY(("_dxf_SET_MATERIAL_SPECULAR (0x%x, %f, %f, %f, %f)",
	 ctx, r, g, b, power));

  power = (power < 0 ? 0 : (power > 127 ? 127 : power)) ;
  color[0] = r ; color[1] = g ; color[2] = b ; color[3] = 1 ;

  glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, power) ;
  glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, color) ;

  OGL_FAIL_ON_ERROR(_dxf_SET_MATERIAL_SPECULAR);
  EXIT((""));
}

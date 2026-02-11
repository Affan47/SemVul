IsSupported(vtkRenderWindow *renWin)
{
  vtkOpenGLRenderWindow *w=static_cast<vtkOpenGLRenderWindow *>(renWin);


  vtkOpenGLExtensionManager *e=w->GetExtensionManager();
  bool supportGS=e->ExtensionSupported("GL_VERSION_3_0")==1 ||
    e->ExtensionSupported("GL_ARB_geometry_shader4")==1 ||
    e->ExtensionSupported("GL_EXT_geometry_shader4")==1;

  return supportGS && vtkTextureObject::IsSupported(renWin) &&
    vtkFrameBufferObject::IsSupported(renWin) &&
    vtkShaderProgram2::IsSupported(w);
}

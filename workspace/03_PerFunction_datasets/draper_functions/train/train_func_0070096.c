SetContext(vtkOpenGLRenderWindow *context)
{
  if(this->Context!=context)
    {
    this->ReleaseGraphicsResources();
    this->Context=context;
    if(this->Context!=0)
      {
      this->ExtensionsLoaded=this->LoadExtensions(this->Context);
      if(this->ExtensionsLoaded)
        {
        vtkOpenGLExtensionManager *e=this->Context->GetExtensionManager();
        bool supportGeometryShaderARB=e->ExtensionSupported("GL_ARB_geometry_shader4")==1;
        this->SupportGeometryShader=supportGeometryShaderARB
          || e->ExtensionSupported("GL_EXT_geometry_shader4")==1;
        if(this->SupportGeometryShader)
          {
          if(supportGeometryShaderARB)
            {
            e->LoadExtension("GL_ARB_geometry_shader4");
            }
          else
            {
            e->LoadAsARBExtension("GL_EXT_geometry_shader4");
            }
          }
        }
      }
    this->Modified();
    }
}

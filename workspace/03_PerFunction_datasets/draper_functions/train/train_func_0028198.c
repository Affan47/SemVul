PrintSelf(ostream& os, vtkIndent indent)
{
  if(this->RenderWindow!=0)
    {
    vtkOpenGLExtensionManager *extensions=
      static_cast<vtkOpenGLRenderWindow *>(this->RenderWindow.GetPointer())
      ->GetExtensionManager();
    if ( this->Initialized )
      {
      os << indent << "Supports GL_VERSION_1_3 (edge_clamp (1.2) and"
         << " multitexture (1.3) minimal version required by"
         << " GL_ARB_draw_buffers): "
         << extensions->ExtensionSupported( "GL_VERSION_1_3" );

      os << indent << "Supports GL_VERSION_2_0 (GL_ARB_draw_buffers is a core"
         << "feature): "
         << extensions->ExtensionSupported( "GL_VERSION_2_0" );

      os << indent << "Supports GL_ARB_draw_buffers: "
         << extensions->ExtensionSupported( "GL_ARB_draw_buffers" );

      os << indent << "Supports GL_EXT_framebuffer_object: "
         << extensions->ExtensionSupported( "GL_EXT_framebuffer_object" )
         << endl;
      os << indent << "Supports GL_ARB_vertex_program: "
         << extensions->ExtensionSupported( "GL_ARB_vertex_program" ) << endl;
      os << indent << "Supports GL_ARB_fragment_program: "
         << extensions->ExtensionSupported( "GL_ARB_fragment_program" ) << endl;
      os << indent << "Supports GL_ARB_texture_float"
         << extensions->ExtensionSupported( "GL_ARB_texture_float" ) << endl;
      os << indent << "Supports GL_ATI_texture_float: "
         << extensions->ExtensionSupported( "GL_ATI_texture_float" ) << endl;

      os << indent << "Supports GL_VERSION_1_5 (for optional core feature VBO): "
         << extensions->ExtensionSupported( "GL_VERSION_1_5" ) <<endl;

      os << indent << "Supports (optional) GL_ARB_vertex_buffer_object: "
         << extensions->ExtensionSupported( "GL_ARB_vertex_buffer_object" )
         <<endl;
      }
    }

  os << indent << "Framebuffer Object Size: "
     << this->FramebufferObjectSize << endl;

  this->Superclass::PrintSelf(os,indent);
}

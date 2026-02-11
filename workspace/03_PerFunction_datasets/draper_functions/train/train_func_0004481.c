Initialize(vtkRenderer *ren,
                                           vtkVolume *vol)
{

  if (!this->SupportedByHardware(ren))
    {
    this->InitializationError = vtkHAVSVolumeMapper::UNSUPPORTED_EXTENSIONS;
    return;
    }

  vtkOpenGLExtensionManager *extensions=
    static_cast<vtkOpenGLRenderWindow *>(ren->GetRenderWindow())
    ->GetExtensionManager();


  extensions->LoadExtension("GL_VERSION_1_3");


  int supports_GL_2_0=extensions->ExtensionSupported( "GL_VERSION_2_0" );

  if(supports_GL_2_0)
    {
    extensions->LoadExtension("GL_VERSION_2_0");
    }
  else
    {
    extensions->LoadCorePromotedExtension( "GL_ARB_draw_buffers" );
    }


  extensions->LoadExtension( "GL_ARB_fragment_program" );
  extensions->LoadExtension( "GL_ARB_vertex_program" );


  extensions->LoadExtension("GL_EXT_framebuffer_object");


  int supports_GL_1_5=extensions->ExtensionSupported( "GL_VERSION_1_5" );
  int supports_vertex_buffer_object;

  if(supports_GL_1_5)
    {
    supports_vertex_buffer_object=1;
    }
  else
    {
    supports_vertex_buffer_object =
      extensions->ExtensionSupported( "GL_ARB_vertex_buffer_object" );
    }

  if(supports_vertex_buffer_object)
    {
    if(supports_GL_1_5)
      {
      extensions->LoadExtension("GL_VERSION_1_5");
      }
    else
      {
      extensions->LoadCorePromotedExtension( "GL_ARB_vertex_buffer_object" );
      }
    }

  if (!supports_vertex_buffer_object)
    {
    this->SetGPUDataStructures(false);
    }

  this->UpdateProgress(0.0);


  this->InitializePrimitives(vol);

  this->UpdateProgress(0.4);


  this->InitializeScalars();

  this->UpdateProgress(0.5);


  this->InitializeLevelOfDetail();

  this->UpdateProgress(0.7);


  this->InitializeLookupTables(vol);

  this->UpdateProgress(0.8);


  this->InitializeGPUDataStructures();

  this->UpdateProgress(0.9);


  this->InitializeShaders();


  this->InitializeFramebufferObject();

  this->UpdateProgress(1.0);

  this->Initialized = 1;
}

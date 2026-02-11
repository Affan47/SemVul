_glewInit_GL_NV_transform_feedback2 ()
{
  GLboolean r = GL_FALSE;

  r = ((glBindTransformFeedbackNV = (PFNGLBINDTRANSFORMFEEDBACKNVPROC)glewGetProcAddress((const GLubyte*)"glBindTransformFeedbackNV")) == NULL) || r;
  r = ((glDeleteTransformFeedbacksNV = (PFNGLDELETETRANSFORMFEEDBACKSNVPROC)glewGetProcAddress((const GLubyte*)"glDeleteTransformFeedbacksNV")) == NULL) || r;
  r = ((glDrawTransformFeedbackNV = (PFNGLDRAWTRANSFORMFEEDBACKNVPROC)glewGetProcAddress((const GLubyte*)"glDrawTransformFeedbackNV")) == NULL) || r;
  r = ((glGenTransformFeedbacksNV = (PFNGLGENTRANSFORMFEEDBACKSNVPROC)glewGetProcAddress((const GLubyte*)"glGenTransformFeedbacksNV")) == NULL) || r;
  r = ((glIsTransformFeedbackNV = (PFNGLISTRANSFORMFEEDBACKNVPROC)glewGetProcAddress((const GLubyte*)"glIsTransformFeedbackNV")) == NULL) || r;
  r = ((glPauseTransformFeedbackNV = (PFNGLPAUSETRANSFORMFEEDBACKNVPROC)glewGetProcAddress((const GLubyte*)"glPauseTransformFeedbackNV")) == NULL) || r;
  r = ((glResumeTransformFeedbackNV = (PFNGLRESUMETRANSFORMFEEDBACKNVPROC)glewGetProcAddress((const GLubyte*)"glResumeTransformFeedbackNV")) == NULL) || r;

  return r;
}

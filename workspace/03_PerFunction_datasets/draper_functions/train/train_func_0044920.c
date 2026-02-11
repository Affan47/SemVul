DestroyFBO()
{
  if(this->FBOIndex!=0)
    {
    GLuint fbo=static_cast<GLuint>(this->FBOIndex);
    vtkgl::DeleteFramebuffersEXT(1,&fbo);
    this->FBOIndex=0;
    }
}

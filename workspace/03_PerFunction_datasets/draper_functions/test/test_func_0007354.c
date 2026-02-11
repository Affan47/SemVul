DestroyBuffer()
{
  if (this->Context && this->Handle)
    {
    GLuint ioBuf = static_cast<GLuint>(this->Handle);
    vtkgl::DeleteBuffers(1, &ioBuf);
    }
  this->Handle = 0;
}

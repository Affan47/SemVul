ActivateBuffers()
{
  GLint maxbuffers;
  glGetIntegerv(vtkgl::MAX_DRAW_BUFFERS, &maxbuffers);

  GLenum *buffers = new GLenum[maxbuffers];
  GLint count=0;
  for(unsigned int cc=0;
      cc < this->ActiveBuffers.size() && count < maxbuffers; cc++)
    {
    buffers[cc] = vtkgl::COLOR_ATTACHMENT0_EXT + this->ActiveBuffers[cc];
    count++;
    }

  vtkgl::DrawBuffers(count, buffers);
  delete[] buffers;
}

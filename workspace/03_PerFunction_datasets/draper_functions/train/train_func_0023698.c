FreeAsciiBuffer()
{
  void* buffer = this->AsciiDataBuffer;
  switch (this->AsciiDataWordType)
    {
    vtkTemplateMacro(
      vtkXMLDataParserFreeAsciiBuffer(static_cast<VTK_TT*>(buffer))
      );
    }
  this->AsciiDataBuffer = 0;
}

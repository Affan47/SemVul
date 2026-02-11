GetVertexShader(int id)
{
  if (id < this->GetNumberOfVertexShaders())
    {
    return this->Internals->VertexShaders[id].GetPointer();
    }
  return NULL;
}

GetTextureAtIndex(int index)
{
  vtkPropertyInternals::MapOfTextures::iterator iter =
    this->Internals->Textures.begin();
  for (int id=0; iter != this->Internals->Textures.end(); ++iter, ++id)
    {
    if (id == index)
      {
      return iter->second.GetPointer();
      }
    }

  vtkErrorMacro("No texture at index " << index );
  return 0;
}

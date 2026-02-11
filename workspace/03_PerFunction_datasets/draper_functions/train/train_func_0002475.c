SetPiece(unsigned int blockno, vtkDataObject* block)
{
  if (block && block->IsA("vtkCompositeDataSet"))
    {
    vtkErrorMacro("Piece cannot be a vtkCompositeDataSet.");
    return;
    }

  this->Superclass::SetChild(blockno, block);
}

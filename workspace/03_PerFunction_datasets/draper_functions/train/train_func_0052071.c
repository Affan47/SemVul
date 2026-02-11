SetModelTransform(vtkMatrix4x4 *mat)
{


  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
      this->ModelTransform->SetElement(i, j, mat->GetElement(i, j));
      }
    }

  if (  this->ModelTransform->GetMTime()
      > this->InverseModelTransform->GetMTime() )
    {
    this->InverseModelTransform->DeepCopy(this->ModelTransform);
    this->InverseModelTransform->Invert();
    }
}

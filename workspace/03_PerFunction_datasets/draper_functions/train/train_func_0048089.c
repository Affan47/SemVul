Pop(vtkTransformConcatenation **concat)
{

  if (this->Stack == this->StackBottom)
    {
    return;
    }


  int preMultiplyFlag = (*concat)->GetPreMultiplyFlag();


  (*concat)->Delete();


  *concat = *--this->Stack;


  (*concat)->SetPreMultiplyFlag(preMultiplyFlag);
}

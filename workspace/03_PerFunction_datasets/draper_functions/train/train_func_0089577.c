SetAlignmentPoint(int val)
{
  vtkWarningMacro(<< "Alignment point is being depricated.  You should use "
                  << "SetJustification and SetVerticalJustification in the text property.");

  switch (val)
    {
    case 0:
      this->TextProperty->SetJustificationToLeft();
      this->TextProperty->SetVerticalJustificationToBottom();
      break;
    case 1:
      this->TextProperty->SetJustificationToCentered();
      this->TextProperty->SetVerticalJustificationToBottom();
      break;
    case 2:
      this->TextProperty->SetJustificationToRight();
      this->TextProperty->SetVerticalJustificationToBottom();
      break;
    case 3:
      this->TextProperty->SetJustificationToLeft();
      this->TextProperty->SetVerticalJustificationToCentered();
      break;
    case 4:
      this->TextProperty->SetJustificationToCentered();
      this->TextProperty->SetVerticalJustificationToCentered();
      break;
    case 5:
      this->TextProperty->SetJustificationToRight();
      this->TextProperty->SetVerticalJustificationToCentered();
      break;
    case 6:
      this->TextProperty->SetJustificationToLeft();
      this->TextProperty->SetVerticalJustificationToTop();
      break;
    case 7:
      this->TextProperty->SetJustificationToCentered();
      this->TextProperty->SetVerticalJustificationToTop();
      break;
    case 8:
      this->TextProperty->SetJustificationToRight();
      this->TextProperty->SetVerticalJustificationToTop();
      break;
    }
}

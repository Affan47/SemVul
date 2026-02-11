sortPartsOnGlobalIds(const vtkLSDynaPart *p1, const vtkLSDynaPart *p2)
    {
    if(p1->GetMaxGlobalPointId() < p2->GetMaxGlobalPointId())
      {
      return true;
      }
      return false;
    }

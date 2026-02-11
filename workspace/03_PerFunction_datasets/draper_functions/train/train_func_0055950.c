MarkModelRealBoundary(vtkPolyData* model, vtkPolyData* modelBoundary)
{
  vtkIdTypeArray* marksArray = vtkIdTypeArray::SafeDownCast(model->GetPointData()->GetArray(MarksArrayName));
  vtkIdType i;
  for (i=0; i<model->GetNumberOfPoints(); i++)
    {
    marksArray->InsertValue(i,NON_VISITED);
    }
  for (i=0; i<modelBoundary->GetNumberOfPoints(); i++)
    {
    marksArray->InsertValue(model->FindPoint(modelBoundary->GetPoint(i)),GLOBAL);
    }
}

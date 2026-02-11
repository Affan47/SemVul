WritePPoints(vtkPoints* points, vtkIndent indent)
{
  ostream& os = *(this->Stream);

  os << indent << "<PPoints>\n";
  if(points)
    {
    this->WritePArray(points->GetData(), indent.GetNextIndent());
    }
  os << indent << "</PPoints>\n";
  os.flush();
  if (os.fail())
    {
    this->SetErrorCode(vtkErrorCode::GetLastSystemError());
    }
}

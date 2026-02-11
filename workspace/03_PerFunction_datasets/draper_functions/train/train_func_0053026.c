ReadVrtFile(vtkUnstructuredGrid *output,
                                   idMapping& mapPointId)
{
  mapPointId.clear();
  FILE *in = this->OpenFile(".vrt");
  if (in == NULL)
    {
    return false;
    }

  const int MAX_LINE = 1024;
  char rawLine[MAX_LINE];

  int lineLabel, errorCount = 0;
  if (
         fgets(rawLine, MAX_LINE, in) != NULL
      && strncmp(rawLine, "PROSTAR_VERTEX", 14) == 0
      && fgets(rawLine, MAX_LINE, in) != NULL
      && sscanf(rawLine, "%d", &lineLabel) == 1
      && lineLabel >= 4000
     )
    {
    vtkDebugMacro(<<"Got PROSTAR_VERTEX header");
    }
  else
    {
    vtkErrorMacro(<<"Error reading header for PROSTAR_VERTEX file");
    ++errorCount;
    }

  vtkPoints *points = vtkPoints::New();

  points->Allocate(10000,20000);

  int lineNr = 2;
  float xyz[3];
  vtkIdType nodeCount = 0;

  while (!errorCount && fgets(rawLine, MAX_LINE, in) != NULL)
    {
    ++lineNr;
    if (sscanf(rawLine, "%d %f %f %f", &lineLabel, xyz, xyz+1, xyz+2) == 4)
      {
      xyz[0] *= this->ScaleFactor;
      xyz[1] *= this->ScaleFactor;
      xyz[2] *= this->ScaleFactor;

      points->InsertNextPoint(xyz);
      vtkIdType nodeId = lineLabel;
      mapPointId.insert(std::make_pair(nodeId, nodeCount));
      ++nodeCount;
      }
    else
      {
      vtkErrorMacro(<<"Error reading point at line " << lineNr);
      ++errorCount;
      }
    }

  points->Squeeze();
  output->SetPoints(points);
  points->Delete();

  vtkDebugMacro(<<"Read points: " << lineNr << " errors: " << errorCount);

  fclose(in);
  return errorCount == 0;
}

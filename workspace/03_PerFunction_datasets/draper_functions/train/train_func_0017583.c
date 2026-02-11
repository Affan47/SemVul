ReadCaseFileFile(char* line)
{
  int fileSet, numTimeSteps, filenameNum, lineRead;

  this->UseFileSetsOn();
  lineRead = this->ReadNextDataLine(line);
  while(lineRead &&
        strncmp(line, "FORMAT", 6) != 0 &&
        strncmp(line, "GEOMETRY", 8) != 0 &&
        strncmp(line, "VARIABLE", 8) != 0 &&
        strncmp(line, "TIME", 4) != 0 &&
        strncmp(line, "FILE", 4) != 0)
    {
    vtkIdList *filenameNums = vtkIdList::New();
    vtkIdList *numSteps = vtkIdList::New();
    sscanf(line, "%*s %*s %d", &fileSet);
    this->FileSets->InsertNextId(fileSet);
    lineRead = this->ReadNextDataLine(line);
    if (strncmp(line, "filename", 8) == 0)
      {
      this->FileSetsWithFilenameNumbers->InsertNextId(fileSet);
      while (lineRead != 0 && strncmp(line, "filename", 8) == 0)
        {
        sscanf(line, "%*s %*s %d", &filenameNum);
        filenameNums->InsertNextId(filenameNum);
        this->ReadNextDataLine(line);
        sscanf(line, "%*s %*s %*s %d", &numTimeSteps);
        numSteps->InsertNextId(numTimeSteps);
        lineRead = this->ReadNextDataLine(line);
        }
      this->FileSetFileNameNumbers->AddItem(filenameNums);
      }
    else
      {
      sscanf(line, "%*s %*s %*s %d", &numTimeSteps);
      numSteps->InsertNextId(numTimeSteps);
      lineRead = this->ReadNextDataLine(line);
      }

    this->FileSetNumberOfSteps->AddItem(numSteps);

    filenameNums->Delete();
    numSteps->Delete();
    lineRead = this->ReadNextDataLine(line);
    }

  return lineRead;
}

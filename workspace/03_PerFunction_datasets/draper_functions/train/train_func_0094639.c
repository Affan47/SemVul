RegisterCell(const int& partType,const vtkIdType &matId,
                    const vtkIdType &npts)
  {
    if(this->Info[partType].size() != 0)
      {
      PartInfo *info = &this->Info[partType].back();
      if(info->partId == matId)
        {

        ++info->numCells;
        info->cellStructureSize += npts;
        }
      else
        {


        PartInfo newInfo(this->Parts[matId],partType,matId,
          (info->startId + info->numCells), npts);
        this->Info[partType].push_back(newInfo);
        }
      }
    else
      {

      PartInfo newInfo(this->Parts[matId],partType,matId,0,npts);
      this->Info[partType].push_back(newInfo);
      }
  }

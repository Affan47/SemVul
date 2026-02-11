SubPoints(Acquisition::Pointer out, Acquisition::Pointer in, int bounds[2])
  {
    PointCollection::Pointer temp;
    if ((this->m_ExtractionOption == PointsOnly) && !m_Ids.empty())
    {
      temp = PointCollection::New();
      int numPoints = in->GetPointNumber();
      for (std::list<int>::const_iterator it = this->m_Ids.begin() ; it != this->m_Ids.end() ; ++it)
      {
        if (*it < numPoints)
        {
          PointCollection::Iterator itP = in->BeginPoint();
          std::advance(itP,*it);
          temp->InsertItem(*itP);
        }
        else
        {
          btkWarningMacro("There is no point with the ID #" + ToString(*it));
        }
      }
    }
    else
      temp = in->GetPoints();

    if ((this->mp_FramesIndex[0] == -1) && (this->mp_FramesIndex[1] == -1))
      out->SetPoints(temp);
    else
    {
      PointCollection::Pointer points = PointCollection::New();
      int numFrames = bounds[1] - bounds[0] + 1;
      for (PointCollection::Iterator it = temp->Begin() ; it != temp->End() ; ++it)
      {
        Point::Pointer point = Point::New();
        point->SetLabel((*it)->GetLabel());
        point->SetDescription((*it)->GetDescription());
        point->SetType((*it)->GetType());
        point->SetFrameNumber(numFrames);
        point->SetValues((*it)->GetValues().block(bounds[0],0,numFrames,3));
        point->SetResiduals((*it)->GetResiduals().block(bounds[0],0,numFrames,1));
        points->InsertItem(point);
      }
      out->SetPoints(points);
    }
  }

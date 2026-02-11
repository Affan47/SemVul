SetPoint(int idx, Point::Pointer point)
  {
    if (this->m_Points->SetItem(idx, point))
    {
      if (point->GetFrameNumber() != this->m_PointFrameNumber)
      {
        btkWarningMacro("Point's frame number is different than acquisition's frame number. Point's frame number is resized.");
        point->SetFrameNumber(this->m_PointFrameNumber);
      }
      this->Modified();
    }

  }

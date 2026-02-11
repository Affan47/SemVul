AppendPoint(Point::Pointer p)
  {
    if (this->m_Points->InsertItem(p))
    {
      if (p->GetFrameNumber() != this->m_PointFrameNumber)
      {
        btkWarningMacro("Point's frame number is different than acquisition's frame number. Point's frame number is resized.");
        p->SetFrameNumber(this->m_PointFrameNumber);
      }
      this->Modified();
    }
  }

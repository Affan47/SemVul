MergeData(Acquisition::Pointer output, Acquisition::Pointer input, int frameNumber) const
  {
    int startFrame = 0;
    if (frameNumber < 0)
      startFrame = abs(frameNumber);
    else
      startFrame = output->GetFirstFrame() - 1;

    for (Acquisition::PointIterator it = input->BeginPoint() ; it != input->EndPoint() ; ++it)
    {
      Point::Pointer p = *(output->FindPoint((*it)->GetLabel()));
      p->GetValues().block(startFrame, 0, abs(frameNumber), 3) = (*it)->GetValues().block(startFrame, 0, abs(frameNumber), 3);
      p->GetResiduals().block(startFrame, 0, abs(frameNumber), 1) = (*it)->GetResiduals().block(startFrame, 0, abs(frameNumber), 1);
    }

    for (Acquisition::AnalogIterator it = input->BeginAnalog() ; it != input->EndAnalog() ; ++it)
    {
      Analog::Pointer ac = *(output->FindAnalog((*it)->GetLabel()));
      ac->GetValues().block(startFrame * input->GetNumberAnalogSamplePerFrame(), 0, abs(frameNumber), 1) = (*it)->GetValues().block(startFrame, 0, abs(frameNumber), 1);
    }
  }

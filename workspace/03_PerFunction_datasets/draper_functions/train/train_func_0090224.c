ReadEliteLabel_p(Acquisition::Pointer output, IEEELittleEndianBinaryFileStream* bifs)
  {
    for (Acquisition::PointIterator it = output->BeginPoint() ; it != output->EndPoint() ; ++it)
    {
      std::string label = btkTrimString(btkTrimString(bifs->ReadString(8)), static_cast<char>(0x00));
      if (!label.empty())
        (*it)->SetLabel(label);
    }
  }

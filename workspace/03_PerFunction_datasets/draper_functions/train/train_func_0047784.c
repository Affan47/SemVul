GetConfig(unsigned long start,
      OBStereo::Shape shape) const
  {
    if (!IsValid())
      return Config();

    return OBTetraPlanarStereo::ToConfig(m_cfg, start, shape);
  }

GetConfig(OBStereo::Shape shape) const
  {
    if (!IsValid())
      return Config();

    return OBTetraPlanarStereo::ToConfig(m_cfg, m_cfg.refs.at(0), shape);
  }

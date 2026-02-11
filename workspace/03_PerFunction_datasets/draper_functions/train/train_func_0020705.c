render(GemState *state)
{
  if (!m_light)return;

  if (m_change) {
    m_change = 0;
    if ( !m_on ){
      glDisable(m_light);
      return;
    }

    glEnable(m_light);


    glLightfv(m_light, GL_DIFFUSE,  m_color);
    glLightfv(m_light, GL_SPECULAR, m_color);
    glLightf(m_light, GL_LINEAR_ATTENUATION, linearAttenuation);
  }

  if (m_on) {

    glLightfv(m_light, GL_POSITION, m_position);
    glLightf(m_light, GL_SPOT_EXPONENT, spotExponent);
    glLightfv(m_light, GL_SPOT_DIRECTION, spotDirection);
    glLightf(m_light, GL_SPOT_CUTOFF, spotCutoff);

    renderDebug();
  }
}

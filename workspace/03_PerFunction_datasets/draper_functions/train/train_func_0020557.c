renderGL(GemState *state)
{
  static const GLfloat a_color[]={0.2,0.2,0.2,1};
  static const GLfloat d_color[]={0.8,0.8,0.8,1};
  static const GLfloat e_color[]={0.0,0.0,0.0,1};
  static const GLfloat s_color[]={0.0,0.0,0.0,1};
  static const GLfloat shininess[]={0.0};

  if (!m_cache || !m_renderOn) return;


  glColor4f(1.f, 1.f, 1.f, 1.f);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  a_color);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  d_color);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, e_color);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s_color);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

  gem::GLStack*stacks=NULL;
  if(state)
  {
    state->reset();

    state->set(GemState::_DIRTY, m_cache->dirty);
    state->VertexDirty=m_cache->vertexDirty;

    state->get(GemState::_GL_STACKS, stacks);
    if(stacks)stacks->push();
  }


  if (GemMan::getProfileLevel() >= 2)
	m_cache->resendImage = 1;

  t_atom ap[2];
  ap->a_type=A_POINTER;
  ap->a_w.w_gpointer=reinterpret_cast<t_gpointer*>(m_cache);
  (ap+1)->a_type=A_POINTER;
  (ap+1)->a_w.w_gpointer=reinterpret_cast<t_gpointer*>(state);
  outlet_anything(this->m_outlet, gensym("gem_state"), 2, ap);

  m_cache->dirty = false;
  m_cache->vertexDirty=false;
  state->get(GemState::_GL_STACKS, stacks);
  if(stacks)stacks->pop();
}

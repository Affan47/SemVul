get_count() const
{
  if(!m_refListStore)
    return 0;

  guint iCount = m_refListStore->children().size();


  if(get_allow_user_actions())
  {
    --iCount;
  }

  return iCount;
}

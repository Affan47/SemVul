needSave(int t)
{
  return (((t-m_t0) % m_dt)==0) && (t>=m_t0) && (t<=m_tend);
}

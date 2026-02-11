CheckRange(const string& s, Params::Size_t size) const
{
   if (size > m_params.m_target)
   {
      cerr << "> [Ignoring] bigger than 'target'("
           << m_params.PrettySize(m_params.m_target) << "): " << s
           << " (" << m_params.PrettySize(size) << ")" << endl;

      return false;
   }

   if (size > m_params.m_max_size)
   {
      cerr << "> [Ignoring] bigger than '--max-size'("
           << m_params.PrettySize(m_params.m_max_size) << "): "
           << s << " (" << m_params.PrettySize(size) << ")" << endl;

      return false;
   }

   if (size <= 0.0)
   {
      cerr << "> [Ignoring] 0-sized input: " << s << endl;

      return false;
   }

   if (size < m_params.m_min_size)
   {
      cerr << "> [Ignoring] smaller than '--min-size'("
           << m_params.PrettySize(m_params.m_min_size) << "): " << s
           << " (" << m_params.PrettySize(size) << ")" << endl;

      return false;
   }

   return true;
}

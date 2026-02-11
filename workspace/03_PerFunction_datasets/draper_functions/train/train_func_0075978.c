free_list_items()
{


   TailFile *tmp;


   while (!m_tailfiles.is_empty())
   {
      tmp = m_tailfiles.first_element();
      m_tailfiles.remove_first();
      delete tmp;
   }
}

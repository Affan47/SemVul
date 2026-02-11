more_to_read()
{


   if (m_file == NULL)
   {

      return 0;
   }


   long end = end_of_file_position();


   if (end < m_position)
   {


      m_position = end;

      return 0;
   }

   return end - m_position;
}

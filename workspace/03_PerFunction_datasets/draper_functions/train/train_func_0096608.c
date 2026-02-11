m_tra2(matrix, m_result)
const hmat2_t *matrix;
hmat2_t *m_result;
{
   m_result = gm_ALLOC(hmat2_t, m_result, "m_tra2()");

   if(m_result != matrix)
   {
     int i,j;

     for(i=0; i<3; i++)
        for(j=0; j<3; j++)
          m_elem(*m_result, i, j) = m_elem(*matrix, j, i);
   }
   else
   {
     double  buf[3];

     buf[0] = m_elem(*matrix, 1, 0);
     buf[1] = m_elem(*matrix, 2, 0);
     buf[2] = m_elem(*matrix, 2, 1);

     m_elem(*m_result, 1, 0) = m_elem(*matrix, 0, 1);
     m_elem(*m_result, 2, 0) = m_elem(*matrix, 0, 2);
     m_elem(*m_result, 2, 1) = m_elem(*matrix, 1, 2);

     m_elem(*m_result, 0, 1) = buf[0];
     m_elem(*m_result, 0, 2) = buf[1];
     m_elem(*m_result, 1, 2) = buf[2];

   };

   return m_result;
}

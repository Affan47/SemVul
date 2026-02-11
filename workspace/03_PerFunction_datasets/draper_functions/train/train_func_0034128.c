m_tra3(matrix, m_result)
const hmat3_t *matrix;
hmat3_t *m_result;
{
   m_result = gm_ALLOC(hmat3_t, m_result, "m_tra3()");

   if(m_result != matrix)
   {
     int i, j;

     m_result = gm_ALLOC(hmat3_t, m_result, "m_tra3()");

     for(i=0; i<4; i++)
        for(j=0; j<4; j++)
          m_elem(*m_result, i, j) = m_elem(*matrix, j, i);
   }
   else
   {
     double  buf[6];

     buf[0] = m_elem(*matrix, 1, 0);
     buf[1] = m_elem(*matrix, 2, 0);
     buf[2] = m_elem(*matrix, 2, 1);
     buf[3] = m_elem(*matrix, 3, 0);
     buf[4] = m_elem(*matrix, 3, 1);
     buf[5] = m_elem(*matrix, 3, 2);


     m_elem(*m_result, 1, 0) = m_elem(*matrix, 0, 1);
     m_elem(*m_result, 2, 0) = m_elem(*matrix, 0, 2);
     m_elem(*m_result, 2, 1) = m_elem(*matrix, 1, 2);
     m_elem(*m_result, 3, 0) = m_elem(*matrix, 0, 3);
     m_elem(*m_result, 3, 1) = m_elem(*matrix, 1, 3);
     m_elem(*m_result, 3, 2) = m_elem(*matrix, 2, 3);

     m_elem(*m_result, 0, 1) = buf[0];
     m_elem(*m_result, 0, 2) = buf[1];
     m_elem(*m_result, 0, 3) = buf[3];
     m_elem(*m_result, 1, 2) = buf[2];
     m_elem(*m_result, 1, 3) = buf[4];
     m_elem(*m_result, 2, 3) = buf[5];
   };

   return m_result;
}

m_inv2(matrix, m_result)
const hmat2_t *matrix;
hmat2_t *m_result;
{
   hmat2_t m_input;
   int i, j;

   m_result = gm_ALLOC(hmat2_t, m_result, "m_inv2()");

   for(i=0; i<3; i++)
     for(j=0; j<3; j++)
        m_elem(*m_result, i, j) = (i!=j) ? 0.0 : 1.0;


   m_input = *matrix;


   for(i=0;i<3;i++)

     reduce_row2(&m_input, m_result, i);

   return  m_result;
}

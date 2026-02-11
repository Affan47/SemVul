mm_mul2(matrixA, matrixB, m_result)
const hmat2_t *matrixA;
const hmat2_t *matrixB;
hmat2_t *m_result;
{
   int row, col, which_matrix;


   hmat2_t buf;

   if(m_result == matrixA)
   {
     m_result = &buf;
     which_matrix = 1;
   }
   else
     if(m_result == matrixB)
     {
        m_result = &buf;
        which_matrix = 2;
     }
     else
     {
        m_result = gm_ALLOC(hmat2_t, m_result, "mm_mul2()");
        which_matrix = 0;
     };

   for(row=0; row<3; row++)
     for(col=0; col<3; col++)
        m_elem(*m_result, row, col) = m_elem(*matrixA, row, 0) * m_elem(*matrixB, 0, col) +
                  m_elem(*matrixA, row, 1) * m_elem(*matrixB, 1, col) + m_elem(*matrixA, row, 2) *
	 	  m_elem(*matrixB, 2, col);

   switch(which_matrix)
   {
     case 0 : return  m_result;
     case 1 :
              *(hmat2_t *)matrixA = *m_result;
              return  (hmat2_t *)matrixA;
     case 2 :
              *(hmat2_t *)matrixB = *m_result;
              return (hmat2_t *)matrixB;
   };
	error_at_line(0, 0, __FILE__, __LINE__, "This should not happen!");
	return m_result;
}

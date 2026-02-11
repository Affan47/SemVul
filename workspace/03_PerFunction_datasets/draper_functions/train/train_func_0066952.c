add_scores(ParseStruct *parsestruct_ptr,
                       double *matrix_row,
                       unsigned long *count_row_fct,
                       short current_row_fct,
                       unsigned long hit_number,
                       unsigned long position,
                       unsigned short k, double score)
{


  if (current_row_fct > 3)
  {
    matrix_row[POSITION(MATRIXSTRUCT(query_to), hit_number, -position, -k)]
      += score;
    count_row_fct[POSITION
                  (MATRIXSTRUCT(query_to), hit_number, -position, -k)] +=
      1;
  }
  else
  {
    matrix_row[POSITION(MATRIXSTRUCT(query_from), hit_number, position, k)]
      += score;
    count_row_fct[POSITION
                  (MATRIXSTRUCT(query_from), hit_number, position, k)] +=
      1;
  }
}

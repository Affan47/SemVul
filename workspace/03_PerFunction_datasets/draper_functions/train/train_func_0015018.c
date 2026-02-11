vect_get_mask_element (gimple stmt, int first_mask_element, int m,
                       int mask_nunits, bool only_one_vec, int index,
                       int *mask, int *current_mask_element,
                       bool *need_next_vector, int *number_of_mask_fixes,
                       bool *mask_fixed, bool *needs_first_vector)
{
  int i;


  *current_mask_element = first_mask_element + m;

  *current_mask_element -= mask_nunits * (*number_of_mask_fixes - 1);

  if (*current_mask_element < mask_nunits)
    *needs_first_vector = true;


  if (only_one_vec && *current_mask_element >= mask_nunits)
    {
      if (vect_print_dump_info (REPORT_DETAILS))
        {
          fprintf (vect_dump, "permutation requires at least two vectors ");
          print_gimple_stmt (vect_dump, stmt, 0, TDF_SLIM);
        }

      return false;
    }


  if (*current_mask_element >= mask_nunits * 2)
    {
      if (*needs_first_vector || *mask_fixed)
        {


          if (vect_print_dump_info (REPORT_DETAILS))
            {
              fprintf (vect_dump, "permutation requires at "
                                  "least three vectors ");
              print_gimple_stmt (vect_dump, stmt, 0, TDF_SLIM);
            }

          return false;
        }


      *current_mask_element -= mask_nunits * *number_of_mask_fixes;

      for (i = 0; i < index; i++)
        mask[i] -= mask_nunits * *number_of_mask_fixes;

      (*number_of_mask_fixes)++;
      *mask_fixed = true;
    }

  *need_next_vector = *mask_fixed;


  if (index == mask_nunits - 1)
    {
      *number_of_mask_fixes = 1;
      *mask_fixed = false;
      *needs_first_vector = false;
    }

  return true;
}

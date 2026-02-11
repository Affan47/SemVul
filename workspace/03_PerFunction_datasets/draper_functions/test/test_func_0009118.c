gl_array_sortedlist_indexof_from_to (gl_list_t list,
                                     gl_listelement_compar_fn compar,
                                     size_t low, size_t high,
                                     const void *elt)
{
  if (!(low <= high && high <= list->count))

    abort ();
  if (low < high)
    {


      do
        {
          size_t mid = low + (high - low) / 2;
          int cmp = compar (list->elements[mid], elt);

          if (cmp < 0)
            low = mid + 1;
          else if (cmp > 0)
            high = mid;
          else
            {


              high = mid;


              while (low < high)
                {
                  size_t mid2 = low + (high - low) / 2;
                  int cmp2 = compar (list->elements[mid2], elt);

                  if (cmp2 < 0)
                    low = mid2 + 1;
                  else if (cmp2 > 0)

                    abort ();
                  else
                    {
                      if (mid2 == low)
                        break;
                      high = mid2 - 1;
                    }
                }
              return low;
            }
        }
      while (low < high);

    }
  return (size_t)(-1);
}

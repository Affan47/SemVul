is_cycle_trace(unsigned int index, guint64 *cvt_cycle)
{

  if(!(get(index) & (CYCLE_COUNTER_LO | CYCLE_COUNTER_HI)))
    return 0;


  int j = index;
  int k = (j + 1) & TRACE_BUFFER_MASK;

  if( (get(j) & CYCLE_COUNTER_LO) &&
      (get(k) & CYCLE_COUNTER_HI) )
    {
      if(get(j) & CYCLE_COUNTER_HI)
        {


          int i = (index - 1) &  TRACE_BUFFER_MASK;
          if( (get(i) & (CYCLE_COUNTER_HI | CYCLE_COUNTER_LO)) &&
              (((get(k) - get(i)) & 0x7fffffff) == 1) )
            return 1;

        }


      if(cvt_cycle) {
        *cvt_cycle = get(k)&0x3fffffff;
        *cvt_cycle = (*cvt_cycle << 32) |
          ((get(j)&0x7fffffff) | (get(k)&0x80000000 ));
      }

      return 2;

    }


  return 1;
}

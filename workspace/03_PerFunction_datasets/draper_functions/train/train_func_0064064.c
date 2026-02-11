clock_multiple(Bit8u cnum, Bit32u cycles)
{
  if (cnum>MAX_COUNTER) {
    BX_ERROR(("Counter number too high in clock"));
  } else {
    counter_type &thisctr = counter[cnum];
    while(cycles>0) {
      if (thisctr.next_change_time==0) {
        if (thisctr.count_written) {
          switch(thisctr.mode) {
          case 0:
            if (thisctr.GATE && (thisctr.write_state!=MSByte_multiple)) {
              decrement_multiple(thisctr, cycles);
            }
            break;
          case 1:
            decrement_multiple(thisctr, cycles);
            break;
          case 2:
            if (!thisctr.first_pass && thisctr.GATE) {
              decrement_multiple(thisctr, cycles);
            }
            break;
          case 3:
            if (!thisctr.first_pass && thisctr.GATE) {
              decrement_multiple(thisctr, 2*cycles);
            }
            break;
          case 4:
            if (thisctr.GATE) {
              decrement_multiple(thisctr, cycles);
            }
            break;
          case 5:
            decrement_multiple(thisctr, cycles);
            break;
          default:
            break;
          }
        }
        cycles-=cycles;
      } else {
        switch(thisctr.mode) {
        case 0:
        case 1:
        case 2:
        case 4:
        case 5:
          if (thisctr.next_change_time > cycles) {
            decrement_multiple(thisctr,cycles);
            thisctr.next_change_time-=cycles;
            cycles-=cycles;
          } else {
            decrement_multiple(thisctr,(thisctr.next_change_time-1));
            cycles-=thisctr.next_change_time;
            clock(cnum);
          }
          break;
        case 3:
          if (thisctr.next_change_time > cycles) {
            decrement_multiple(thisctr,cycles*2);
            thisctr.next_change_time-=cycles;
            cycles-=cycles;
          } else {
            decrement_multiple(thisctr,(thisctr.next_change_time-1)*2);
            cycles-=thisctr.next_change_time;
            clock(cnum);
          }
          break;
        default:
          cycles-=cycles;
          break;
        }
      }
    }
#if 0
    print_counter(thisctr);
#endif
  }
}

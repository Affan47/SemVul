pushstk(stkitem val)
{
   if (stkidx >= sSTKMAX)
      error(102, "parser stack");
   stack[stkidx] = val;
   stkidx += 1;
}

add_logs(lx, ly)
double lx, ly;
{
   if (lx > ly)  return(lx + log(1.0 + exp(ly - lx)));
   else          return(ly + log(1.0 + exp(lx - ly)));
}

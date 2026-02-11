print_contents(int obj,int ind_lev)


{
  int i, cnt;

  cnt=0;

  contloop(i,obj) {
      if (print_obj(i,ind_lev)) cnt++;
      if (it_open(i)) print_contents(i,ind_lev+1);
    }
  return cnt;
}

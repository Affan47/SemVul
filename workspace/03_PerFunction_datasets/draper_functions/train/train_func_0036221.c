box_hash(ap_manager_t* man, box_t* a)
{
  int i,dec,size,res;
  size = a->intdim +a->realdim;
  res = size * 2999;

  if (a->p!=NULL){
    for (i=0; i<size; i += (size+4)/5){
      res = 3*res + itv_hash(a->p[i]);
    }
  }
  man->result.flag_best = true;
  man->result.flag_exact = true;
  return res;
}

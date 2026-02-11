Optimize_One_Dist(allseq *data, int numseq1, int numseq2, double init_dist, model *mod)
{

  int n_iter, n_iter_mov;
  double lk_new,lk_old,lk_best;
  double step;
  double dlk,d2lk;
  double dist_new,dist_best;

  step = .0;
  dlk  = d2lk = .0;
  lk_old = lk_new = lk_best = .0;
  dist_new = dist_best = init_dist;

  n_iter = 0;
  for(;;)
    {

      if(dist_new < BL_MIN) dist_new = BL_MIN;

      Lk_Given_Two_Seq(data,numseq1,numseq2,dist_new,mod,&lk_new,&dlk,&d2lk);

      if(((fabs(lk_new - lk_old) < MIN_DIFF_LK) && (lk_new >= lk_old)))
	break;
      else
	{
	  if(((fabs(lk_new - lk_old) > MIN_DIFF_LK)
	      && (lk_new > lk_old))
	      || (!n_iter))
	    {
	      dist_best = dist_new;
	      lk_best   = lk_new;
	      lk_old    = lk_new;
	    }
	  else
	    {
	      n_iter_mov = 20;
	      do
		{
		  dist_new = dist_best;
		  step /= 2.;
		  dist_new += step;
		  Lk_Given_Two_Seq(data,numseq1,numseq2,
				   dist_new,mod,&lk_new,&dlk,&d2lk);
		  n_iter_mov--;
		  if(!n_iter_mov) return dist_best;
		}while(lk_new < lk_best);
	      dlk = .0;
	    }
	}

      step = -dlk/d2lk;

      if(d2lk > 0.0)
	{
	  step = .0;
	  dist_new /= 1.5;
	}

      while(fabs(step) > dist_new) step /= 1.5;
      dist_new += step;


      n_iter++;
      if(n_iter > 50) break;
    }
  return dist_new;
}

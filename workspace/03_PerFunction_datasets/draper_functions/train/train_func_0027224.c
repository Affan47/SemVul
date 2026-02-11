adjust_rcut(double time)
{
  if (strcmp(force->kspace_style,"msm") == 0) return;
  if (converged) return;

  double temp;
  const double TINY = 1.0e-20;


  int itmp;
  double *p_cutoff = (double *) force->pair->extract("cut_coul",itmp);
  double current_cutoff = *p_cutoff;
  cout << "Old Coulomb cutoff for real space: " << current_cutoff << endl;


  if (keep_bracketing) {
    if (niter_adjust_rcut == 0) {
      pair_cut_coul /= 2;
    } else if (niter_adjust_rcut == 1) {
      ax_brent = current_cutoff;
      fa_brent = time;
      pair_cut_coul *= 2;


    } else if (niter_adjust_rcut == 2) {
      bx_brent = current_cutoff;
      fb_brent = time;
      if (fb_brent > fa_brent) {
        SWAP(ax_brent,bx_brent);
        SWAP(fb_brent,fa_brent);
        pair_cut_coul /= 4;
      } else {
        pair_cut_coul *= 2;
      }


    } else if (niter_adjust_rcut == 3) {
      cx_brent = current_cutoff;
      fc_brent = time;
      if (fc_brent > fb_brent) keep_bracketing = false;
      else {
        double r = (bx_brent - ax_brent)*(fb_brent - fc_brent);
        double q = (bx_brent - cx_brent)*(fb_brent - fa_brent);
        dx_brent = bx_brent - ((bx_brent - cx_brent)*q - (bx_brent - ax_brent)*r)/
         (2.0*SIGN(MAX(fabs(q - r),TINY),q - r));
        pair_cut_coul = dx_brent;
      }


    } else if (niter_adjust_rcut > 3) {
      dx_brent = current_cutoff;
      if (need_fd2_brent) fd2_brent = time;
      else fd_brent = time;
      mnbrak();
      pair_cut_coul = dx_brent;
    }
  }

  if (!keep_bracketing) {
    dx_brent = current_cutoff;
    fd_brent = time;
    if (first_brent_pass) brent0();
    else brent2();
    brent1();
    pair_cut_coul = dx_brent;
  }

  niter_adjust_rcut++;

  if (pair_cut_coul <= 0.0) pair_cut_coul = fabs(MIN(ax_brent,MIN(bx_brent,(MIN(cx_brent,dx_brent))))/2.0) + TINY;

  if (pair_cut_coul != pair_cut_coul)
    error->all(FLERR,"Bad real space Coulomb cutoff in fix tune/kspace");


  *p_cutoff = pair_cut_coul;


  double *new_cutoff = (double *) force->pair->extract("cut_coul",itmp);
  current_cutoff = *new_cutoff;
  cout << "Adjusted Coulomb cutoff for real space: " << current_cutoff << endl;

  store_old_kspace_settings();
  update_pair_style(new_pair_style,pair_cut_coul);
  update_kspace_style(new_kspace_style,new_acc_str);
}

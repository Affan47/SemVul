IncreaseQuality()
  {
    if (control_.u >= umax_) {
      return false;
    }
    pivtol_changed_ = true;

    Jnlst().Printf(J_DETAILED, J_LINEAR_ALGEBRA,
                   "Increasing pivot tolerance for HSL_MA86 from %7.2e ",
                   control_.u);
    control_.u = Min(umax_, pow(control_.u,0.75));
    Jnlst().Printf(J_DETAILED, J_LINEAR_ALGEBRA,
                   "to %7.2e.\n",
                   control_.u);
    return true;
  }

}

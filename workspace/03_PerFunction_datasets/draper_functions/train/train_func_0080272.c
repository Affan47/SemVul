UpdateBarrierParameter()
  {
    Jnlst().Printf(J_DETAILED, J_MAIN, "\n**************************************************\n");
    Jnlst().Printf(J_DETAILED, J_MAIN, "*** Update Barrier Parameter for Iteration %d:", IpData().iter_count());
    Jnlst().Printf(J_DETAILED, J_MAIN, "\n**************************************************\n\n");
    bool retval = mu_update_->UpdateBarrierParameter();

    if (retval) {
      Jnlst().Printf(J_DETAILED, J_MAIN,
                     "Barrier Parameter: %e\n", IpData().curr_mu());
    }
    else {
      Jnlst().Printf(J_DETAILED, J_MAIN,
                     "Barrier parameter could not be updated!\n");
    }

    return retval;
  }

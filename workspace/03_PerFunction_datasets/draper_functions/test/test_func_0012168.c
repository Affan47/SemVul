PrintTimingStatistics(
    Journalist& jnlst,
    EJournalLevel level,
    EJournalCategory category) const
  {
    if (!jnlst.ProduceOutput(level, category))
      return;

    jnlst.Printf(level, category,
                 "Function Evaluations................: %10.3f (sys: %10.3f wall: %10.3f)\n",
                 TotalFunctionEvaluationCpuTime(),
                 TotalFunctionEvaluationSysTime(),
                 TotalFunctionEvaluationWallclockTime());
    jnlst.Printf(level, category,
                 " Objective function.................: %10.3f (sys: %10.3f wall: %10.3f)\n",
                 f_eval_time_.TotalCpuTime(),
                 f_eval_time_.TotalSysTime(),
                 f_eval_time_.TotalWallclockTime());
    jnlst.Printf(level, category,
                 " Objective function gradient........: %10.3f (sys: %10.3f wall: %10.3f)\n",
                 grad_f_eval_time_.TotalCpuTime(),
                 grad_f_eval_time_.TotalSysTime(),
                 grad_f_eval_time_.TotalWallclockTime());
    jnlst.Printf(level, category,
                 " Equality constraints...............: %10.3f (sys: %10.3f wall: %10.3f)\n",
                 c_eval_time_.TotalCpuTime(),
                 c_eval_time_.TotalSysTime(),
                 c_eval_time_.TotalWallclockTime());
    jnlst.Printf(level, category,
                 " Inequality constraints.............: %10.3f (sys: %10.3f wall: %10.3f)\n",
                 d_eval_time_.TotalCpuTime(),
                 d_eval_time_.TotalSysTime(),
                 d_eval_time_.TotalWallclockTime());
    jnlst.Printf(level, category,
                 " Equality constraint Jacobian.......: %10.3f (sys: %10.3f wall: %10.3f)\n",
                 jac_c_eval_time_.TotalCpuTime(),
                 jac_c_eval_time_.TotalSysTime(),
                 jac_c_eval_time_.TotalWallclockTime());
    jnlst.Printf(level, category,
                 " Inequality constraint Jacobian.....: %10.3f (sys: %10.3f wall: %10.3f)\n",
                 jac_d_eval_time_.TotalCpuTime(),
                 jac_d_eval_time_.TotalSysTime(),
                 jac_d_eval_time_.TotalWallclockTime());
    jnlst.Printf(level, category,
                 " Lagrangian Hessian.................: %10.3f (sys: %10.3f wall: %10.3f)\n",
                 h_eval_time_.TotalCpuTime(),
                 h_eval_time_.TotalSysTime(),
                 h_eval_time_.TotalWallclockTime());
  }

GetStopConditionDescription() const
{
  m_StopConditionDescription.str("");
  m_StopConditionDescription << this->GetNameOfClass() << ": ";
  if ( m_VnlOptimizer )
    {
    switch ( m_VnlOptimizer->get_failure_code() )
      {
      case vnl_nonlinear_minimizer::ERROR_FAILURE:
        m_StopConditionDescription << "Failure";
        break;
      case vnl_nonlinear_minimizer::ERROR_DODGY_INPUT:
        m_StopConditionDescription << "Dodgy input";
        break;
      case vnl_nonlinear_minimizer::CONVERGED_FTOL:
        m_StopConditionDescription << "Function tolerance reached";
        break;
      case vnl_nonlinear_minimizer::CONVERGED_XTOL:
        m_StopConditionDescription << "Solution tolerance reached";
        break;
      case vnl_nonlinear_minimizer::CONVERGED_XFTOL:
        m_StopConditionDescription << "Solution and Function tolerance both reached";
        break;
      case vnl_nonlinear_minimizer::CONVERGED_GTOL:
        m_StopConditionDescription << "Gradient tolerance reached";
        break;
      case vnl_nonlinear_minimizer::FAILED_TOO_MANY_ITERATIONS:
        m_StopConditionDescription << "Too many function evaluations. Function evaluations  = "
                                   << m_MaximumNumberOfFunctionEvaluations;
        break;
      case vnl_nonlinear_minimizer::FAILED_FTOL_TOO_SMALL:
        m_StopConditionDescription << "Function tolerance too small";
        break;
      case vnl_nonlinear_minimizer::FAILED_XTOL_TOO_SMALL:
        m_StopConditionDescription << "Solution tolerance too small";
        break;
      case vnl_nonlinear_minimizer::FAILED_GTOL_TOO_SMALL:
        m_StopConditionDescription << "Gradient tolerance too small";
        break;
      case vnl_nonlinear_minimizer::FAILED_USER_REQUEST:
        m_StopConditionDescription << "User requested";
        break;
      }
    return m_StopConditionDescription.str();
    }
  else
    {
    return std::string("");
    }
}

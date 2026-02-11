SetMetric(MetricType *metric)
{
  Superclass::SetMetric( metric );

  CostFunctionAdaptorType *adaptor = this->GetCostFunctionAdaptor();

  m_VnlOptimizer.Reset();
  m_VnlOptimizer.TakeOwnership( new InternalOptimizerType( *adaptor, this ) );


  m_VnlOptimizer->set_trace( m_Trace );
  m_VnlOptimizer->set_lower_bound( m_LowerBound );
  m_VnlOptimizer->set_upper_bound( m_UpperBound );
  m_VnlOptimizer->set_bound_selection( m_BoundSelection );
  m_VnlOptimizer->set_cost_function_convergence_factor( m_CostFunctionConvergenceFactor );
  m_VnlOptimizer->set_projected_gradient_tolerance( m_GradientConvergenceTolerance );
  m_VnlOptimizer->set_max_function_evals( static_cast< int >( m_MaximumNumberOfFunctionEvaluations ) );
  m_VnlOptimizer->set_max_variable_metric_corrections( m_MaximumNumberOfCorrections );

  m_OptimizerInitialized = true;

  this->Modified();
}

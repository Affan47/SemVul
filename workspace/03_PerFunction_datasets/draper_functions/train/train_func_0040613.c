StartOptimization( void )
{
  unsigned int j, k, n, index, prevIndex;
  bool converged = false;
  unsigned int bestValueMemorySize =
    this->m_NumberOfGenerationsWithMinimalImprovement+1;
  unsigned int percentileIndex =
    static_cast<unsigned int>( this->m_PercentageParticlesConverged*
                               (this->m_NumberOfParticles-1) + 0.5 );

  ValidateSettings();

  Initialize();

  InvokeEvent( StartEvent() );


  n = static_cast<unsigned int>( ( GetCostFunction() )->GetNumberOfParameters() );
  for( this->m_IterationIndex=1; m_IterationIndex<m_MaximalNumberOfIterations && !converged; m_IterationIndex++ )
    {

    UpdateSwarm();


    for( j=0; j<this->m_NumberOfParticles; j++ )
      {
      if( this->m_Particles[j].m_BestValue < m_FunctionBestValue )
        {
        this->m_FunctionBestValue = m_Particles[j].m_BestValue;
        this->m_ParametersBestValue = m_Particles[j].m_BestParameters;
        }
      }

    SetCurrentPosition( this->m_ParametersBestValue );


    index = this->m_IterationIndex%bestValueMemorySize;
    this->m_FunctionBestValueMemory[index] = m_FunctionBestValue;


    if( this->m_IterationIndex>=m_NumberOfGenerationsWithMinimalImprovement )
      {
      if( index ==  this->m_NumberOfGenerationsWithMinimalImprovement )
        prevIndex = 0;
      else
        prevIndex = index+1;


      if( ( this->m_FunctionBestValueMemory[prevIndex] -
            this->m_FunctionBestValueMemory[index] ) <
            this->m_FunctionConvergenceTolerance )
        {
        converged = true;
        std::vector<ParametersType::ValueType> parameterDiffs( this->m_NumberOfParticles );
        for( k=0; k<n && converged; k++ )
          {
          for( j=0; j<this->m_NumberOfParticles; j++ )
            {
              parameterDiffs[j] =
                fabs( this->m_Particles[j].m_BestParameters[k] -
                      this->m_ParametersBestValue[k] );
            }
          std::nth_element( parameterDiffs.begin(),
                            parameterDiffs.begin()+percentileIndex,
                            parameterDiffs.end() );
          converged = converged &&
                      parameterDiffs[percentileIndex] < this->m_ParametersConvergenceTolerance[k];
          }
        }
      }
    InvokeEvent( IterationEvent() );
    }

    this->m_StopConditionDescription << GetNameOfClass() << ": ";
    if( converged )
      this->m_StopConditionDescription << "successfuly converged after "<< m_IterationIndex <<" iterations";
    else
      this->m_StopConditionDescription << "terminated after "<< m_IterationIndex <<" iterations";
    InvokeEvent( EndEvent() );
}

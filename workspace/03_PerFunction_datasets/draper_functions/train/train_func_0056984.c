IsThisInputVariableInstanceNeeded( int a_timestep, int a_outputTimestep )
{
  if(a_outputTimestep<a_timestep)
    {
    int l_index = a_timestep-a_outputTimestep;
    if( (int)(this->ForwardNumeratorWeights->m_vector.size())>=l_index )
      {


      return(true);
      }
    else
      {


      return(false);
      }
    }
  if( this->DenominatorWeights->m_vector.size() > 1 )
    {


    return(true);
    }


  if( a_timestep < a_outputTimestep-((int)(this->NumeratorWeights->m_vector.size())-1) )
    {

    return(false);
    }
  return(true);
}

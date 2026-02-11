AddInputVariableInstance( const char *a_name, int a_timestep, vtkFloatArray *a_data )
{


  this->CachedInputTimesteps->m_vector.push_back(a_timestep);
  this->CachedInputNames->m_vector.push_back(a_name);

  vtkFloatArray *l_array = vtkFloatArray::New();
  l_array->DeepCopy(a_data);
  this->CachedInputs->m_vector.push_back(l_array);
}

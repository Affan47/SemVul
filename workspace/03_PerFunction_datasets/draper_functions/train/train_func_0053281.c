setDiscretizationData(int nof_components, linDeltaType* types, double* valuesU, double* valuesV, bool* useFixedN)
{
  if ( ptrGmtr == NULL ) return;

  ptrGmtr->setDiscretizationData(nof_components, types, valuesU, valuesV, useFixedN);
}

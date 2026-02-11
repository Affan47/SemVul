getDiscretizationData(int& nof_components, linDeltaType*& types, double*& valuesU, double*& valuesV, bool*& useFixedN)
{
  nof_components = data.nofEmfComponents;

  types = new linDeltaType[nof_components];
  valuesU = new double[nof_components];
  useFixedN = new bool[nof_components];

  for (int i = 0; i < nof_components; i++) {

    Geometry* sc = data.emfComponents[i];

    types[i] = sc->getDeltaType();
    valuesU[i] = sc->getDeltaU();
    useFixedN[i] = sc->useFixedMeshN();
  }
}

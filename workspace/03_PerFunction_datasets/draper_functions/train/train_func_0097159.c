doPatchMeshShFill(GfxPatchMeshShading *shading) {
  int start, i;

  if (out->useShadedFills( shading->getType())) {
    if (out->patchMeshShadedFill( state, shading))
      return;
  }

  if (shading->getNPatches() > 128) {
    start = 3;
  } else if (shading->getNPatches() > 64) {
    start = 2;
  } else if (shading->getNPatches() > 16) {
    start = 1;
  } else {
    start = 0;
  }


  const int colorComps = shading->getColorSpace()->getNComps();
  double refineColorThreshold;
  if( shading->isParameterized() ) {
	  refineColorThreshold = gouraudParameterizedColorDelta *
		  (shading->getParameterDomainMax() - shading->getParameterDomainMin());

  } else {
	  refineColorThreshold = patchColorDelta;
  }

  for (i = 0; i < shading->getNPatches(); ++i) {
    fillPatch(shading->getPatch(i),
             colorComps,
             shading->isParameterized() ? 1 : colorComps,
             refineColorThreshold,
             start,
             shading);
  }
}

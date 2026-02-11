amdmsCreateFlatfieldMap(amdmsALGO_PROPERTIES_ENV *env,
				 amdmsFITS *outfile,
				 amdmsFITS_FLAGS flags)
{
  if (amdmsUpdateKeywordString(outfile, "HIERARCH ESO DPR CATG", "CALIB", "Observation category")  != amdmsSUCCESS) {
    return amdmsFAILURE;
  }
  if (amdmsUpdateKeywordString(outfile, "HIERARCH ESO DPR TECH", "INTERFEROMETRY", "Observation technique") != amdmsSUCCESS) {
    return amdmsFAILURE;
  }
  if (amdmsUpdateKeywordString(outfile, "HIERARCH ESO DPR TYPE", "FLATFIELD", "Observation type") != amdmsSUCCESS) {
    return amdmsFAILURE;
  }
  if (amdmsCreateData(outfile, flags, amdmsFLATFIELD_NROWS, 1) != amdmsSUCCESS) {
    return amdmsFAILURE;
  }
  env->env.calib.ffmData.index = 1.0;
  if (amdmsWriteData(outfile, &(env->env.calib.ffmData), amdmsFLATFIELD_ROW, 0) != amdmsSUCCESS) {
    return amdmsFAILURE;
  }
  return amdmsSUCCESS;
}

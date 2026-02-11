dumpToFile(FILE* f){
  fprintf(f, "DISTORTION TRANSITION PARAMETERS\n");

  for (int c=0; c<rankPartitionFeature; c++){
    for (int i=0; i<MAXLEN*2; i++){
      if (distortionCount[c][i] > 0.0){
	fprintf(f, "DIST %d %d %.6g\n", c, i-MAXLEN, distortionCount[c][i]);
      }
    }
  }

  if (useInitCount){
    fprintf(f, "\n");
    for (int i=0; i<MAXLEN; i++){
      if (initCount[i] > 0.0){
	fprintf(f, "INIT %d %.6g\n", i, initCount[i]);
      }
    }
    fprintf(f, "\n");
  }

  if (useTermCount){
    for (int i=0; i<MAXLEN; i++){
      if (termCount[i] > 0.0){
	fprintf(f, "TERM %d %.6g\n", i, termCount[i]);
      }
    }
  }
}

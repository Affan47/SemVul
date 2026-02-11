PrintParameters (const char *message, const VF &initDistrib, const VF &gapOpen,
                      const VF &gapExtend, const VVF &emitPairs, const VF &emitSingle, const char *filename){


  cerr << message << endl
       << "    initDistrib[] = { ";
  for (int i = 0; i < NumMatrixTypes; i++) cerr << setprecision (10) << initDistrib[i] << " ";
  cerr << "}" << endl
       << "        gapOpen[] = { ";
  for (int i = 0; i < NumInsertStates*2; i++) cerr << setprecision (10) << gapOpen[i] << " ";
  cerr << "}" << endl
       << "      gapExtend[] = { ";
  for (int i = 0; i < NumInsertStates*2; i++) cerr << setprecision (10) << gapExtend[i] << " ";
  cerr << "}" << endl
       << endl;


  if (filename){


    FILE *file = fopen (filename, "w");
    if (!file){
      cerr << "ERROR: Unable to write parameter file: " << filename << endl;
      exit (1);
    }


    for (int i = 0; i < NumMatrixTypes; i++) fprintf (file, "%.10f ", initDistrib[i]); fprintf (file, "\n");
    for (int i = 0; i < 2*NumInsertStates; i++) fprintf (file, "%.10f ", gapOpen[i]); fprintf (file, "\n");
    for (int i = 0; i < 2*NumInsertStates; i++) fprintf (file, "%.10f ", gapExtend[i]); fprintf (file, "\n");
    fprintf (file, "%s\n", alphabet.c_str());
    for (int i = 0; i < (int) alphabet.size(); i++){
      for (int j = 0; j <= i; j++)
	fprintf (file, "%.10f ", emitPairs[(unsigned char) alphabet[i]][(unsigned char) alphabet[j]]);
      fprintf (file, "\n");
    }
    for (int i = 0; i < (int) alphabet.size(); i++)
      fprintf (file, "%.10f ", emitSingle[(unsigned char) alphabet[i]]);
    fprintf (file, "\n");
    fclose (file);
  }
}

CEM(char *CluFile , int Recurse , int InitRand )  {
	int p, c, i;
	int nChanged;
	int Iter;
	Array<int> OldClass(nPoints);
	float Score, OldScore;
	int LastStepFull;
    int DidSplit;

    if (CluFile && *CluFile) LoadClu(CluFile);
	else if (InitRand) {

        if (nStartingClusters>1)
    	    for(p=0; p<nPoints; p++) Class[p] = irand(1, nStartingClusters-1);
        else
            for(p=0; p<nPoints; p++) Class[p] = 0;

		for(c=0; c<MaxPossibleClusters; c++) ClassAlive[c] = (c<nStartingClusters);
    }


    Reindex();


	Iter = 0;
	FullStep = 1;
	do {

		for(p=0; p<nPoints; p++) OldClass[p] = Class[p];


		MStep();


		EStep();


		if (DistDump) MatPrint(Distfp, LogP.m_Data, DistDump, MaxPossibleClusters);


		CStep();


		if(Recurse) ConsiderDeletion();


		nChanged = 0;
		for(p=0; p<nPoints; p++) nChanged += (OldClass[p] != Class[p]);


		OldScore = Score;
		Score = ComputeScore();

		if(Verbose>=1) {
            if(Recurse==0) Output("\t");
            Output("Iteration %d%c: %d clusters Score %.7g nChanged %d\n",
			    Iter, FullStep ? 'F' : 'Q', nClustersAlive, Score, nChanged);
        }

		Iter++;

		if (Debug) {
			for(p=0;p<nPoints;p++) BestClass[p] = Class[p];
			SaveOutput(BestClass);
			Output("Press return");
			getchar();
		}


		LastStepFull = FullStep;
		FullStep = (
						nChanged>ChangedThresh*nPoints
						|| nChanged == 0
						|| Iter%FullStepEvery==0


					) ;
		if (Iter>MaxIter) {
			Output("Maximum iterations exceeded\n");
			break;
		}


        if ((Recurse && SplitEvery>0) && (Iter%SplitEvery==SplitEvery-1 || (nChanged==0 && LastStepFull))) {
            DidSplit = TrySplits();
        } else DidSplit = 0;

	} while (nChanged > 0 || !LastStepFull || DidSplit);

	if (DistDump) fprintf(Distfp, "\n");

	return Score;
}

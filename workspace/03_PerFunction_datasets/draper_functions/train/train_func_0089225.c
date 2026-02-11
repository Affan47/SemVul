matrixInitializeSuperLU(matrix_ *r, control_ *control)
{
	matrixLibrary_ *p;

	ReturnErrIf(r == NULL);
	ReturnErrIf(r->library != NULL);

	Debug("Configuring Solution %p", r);

	r->name = matrixNameSuperLU;
	r->unconfig = matrixUnconfigSuperLU;
	r->solve = matrixSolveSuperLU;
	r->solveAgain = matrixSolveAgainSuperLU;

	r->library = calloc(1, sizeof(matrixLibrary_));
	ReturnErrIf(r->library == NULL);

	p = r->library;


	dCreate_CompCol_Matrix(&p->A, r->lenXB, r->lenXB, r->lenA, r->A,
			r->aRow, r->aColStart, SLU_NC, SLU_D, SLU_GE);


	dCreate_Dense_Matrix(&p->B, r->lenXB, 1, r->B, r->lenXB,
			SLU_DN, SLU_D, SLU_GE);

	dCreate_Dense_Matrix(&p->X, r->lenXB, 1, r->X, r->lenXB,
			SLU_DN, SLU_D, SLU_GE);


	p->perm_r = intMalloc(r->lenXB);
	ReturnErrIf(p->perm_r == NULL);
	p->perm_c = intMalloc(r->lenXB);
	ReturnErrIf(p->perm_r == NULL);
	p->etree = intMalloc(r->lenXB);
	ReturnErrIf(p->etree == NULL);
	p->R = (double *) SUPERLU_MALLOC(p->A.nrow * sizeof(double));
	ReturnErrIf(p->R == NULL);
	p->C = (double *) SUPERLU_MALLOC(p->A.ncol * sizeof(double));
	ReturnErrIf(p->C == NULL);
	p->ferr = (double *) SUPERLU_MALLOC(1 * sizeof(double));
	ReturnErrIf(p->ferr == NULL);
	p->berr = (double *) SUPERLU_MALLOC(1 * sizeof(double));
	ReturnErrIf(p->berr == NULL);


	p->control.Fact = DOFACT;
	p->control.Equil = NO;
	p->control.ColPerm = COLAMD;
	p->control.Trans = NOTRANS;
	p->control.IterRefine = NOREFINE;
	p->control.PrintStat = NO;
	p->control.SymmetricMode = NO;
	p->control.DiagPivotThresh = 1.0;
	p->control.PivotGrowth = NO;
	p->control.ConditionNumber = NO;


    StatInit(&p->stat);


	p->firstPass = -1;

	return 0;
}

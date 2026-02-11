overlapCGTF(CGTF* left, CGTF* right)
{
	gdouble sum=0.0;
	gint n;
	gint np;

	for(n=0;n<left->numberOfFunctions;n++)
		for(np=0;np<right->numberOfFunctions;np++)
			sum += overlapGTF(&(left->Gtf[n]),&(right->Gtf[np]));

	return sum;
}

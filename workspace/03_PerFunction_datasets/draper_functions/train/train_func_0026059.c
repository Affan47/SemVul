bringGuiltyBlock(diag_iter start, diag_iter& end)
{
	double av = b->getAverageDiagSize(start, end);
	diag_iter guilty = b->findClosestDiagBlock(end, b->diag_end(), av);
	SchurDecompEig sd((QuasiTriangular&)*b);
	end = sd.bubbleEigen(guilty, end);
	++end;
	q->multRight(sd.getQ());
	invq->multLeftTrans(sd.getQ());
}

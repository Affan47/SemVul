cleanup(CleanupStage)
{
    for (int i = 0; i < NPLANE; i++) {
	if (Packet ***p = _packets[i]) {
	    for (int j = 0; j < NCOL; j++)
		if (Packet **q = p[j]) {
		    for (int k = 0; k < NROW; k++)
			if (q[k])
			    q[k]->kill();
		    delete[] q;
		}
	    delete[] p;
	}
	delete[] _counts[i];
    }
}

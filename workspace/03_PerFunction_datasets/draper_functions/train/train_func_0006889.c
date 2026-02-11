insrtHeap(long i,keytyp k, dh_type H)

{
	if(i<1) dheap_error("fatal! item to insert is < 1");
	if(H->pos[i]!=0) rmHeap(i,H);
	H->kvec[i] = k; H->n++; siftupHeap(i,H->n,H);
}

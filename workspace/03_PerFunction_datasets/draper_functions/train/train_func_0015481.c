_heap_bubble_up(struct heap *h, int e)
{
	int e1;
	while (e > 1)
	{
		e1 = e/2;
		if(h->cmp(*HELEMENT(h, e1),*HELEMENT(h,e)) < 0) break;
		heap_swap(HELEMENT(h,e),HELEMENT(h,e1));
		e = e1;
	}

}

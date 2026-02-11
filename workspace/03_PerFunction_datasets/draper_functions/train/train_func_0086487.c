hufftree_from_heap (void)
{
	int top, newidx  ;
	struct huff h;

	for (;;)
	{
		if (heap_end == 2) {

			break;
		}


		top = 1;


		newidx = huff_end++;

		h.isleaf = FALSE;
		h.value = -1;
		h.freq =  heap[top].freq;
		h.pleft = heap[top].huffidx;
		h.pright = -1;


	#ifdef TRACE
	printf ("\n\nBefore Eliminate Top\n");
	heap_plot();
	#endif


		heap[top] = heap[--heap_end];


		heap_adjust_down (1, heap_end-1);

	#ifdef TRACE
	printf ("\n\nEliminate Top\n");
	heap_plot ();
	#endif


		h.pright = heap[1].huffidx;
		h.freq += heap[1].freq;
		hufftree[newidx] = h;

		heap[1].freq = h.freq;
		heap[1].huffidx = newidx;


		heap_adjust_down (1, heap_end-1);

	#ifdef TRACE
	printf ("\n\nAfter Combine\n");
	heap_plot ();
	#endif

	}

	return heap[1].huffidx;
}

end_gc(CELL gc_elapsed)
{
	F_GC_STATS *s = &gc_stats[collecting_gen];

	s->collections++;
	s->gc_time += gc_elapsed;
	if(s->max_gc_time < gc_elapsed)
		s->max_gc_time = gc_elapsed;

	if(growing_data_heap)
	{
		dealloc_data_heap(old_data_heap);
		old_data_heap = NULL;
		growing_data_heap = false;
	}

	if(collecting_accumulation_gen_p())
	{


		if(collecting_gen != NURSERY)
			reset_generations(NURSERY,collecting_gen - 1);
	}
	else if(HAVE_NURSERY_P && collecting_gen == NURSERY)
	{
		nursery.here = nursery.start;
	}
	else
	{


		reset_generations(NURSERY,collecting_gen);
	}

	if(collecting_gen == TENURED)
	{


		free_unmarked(&code_heap);
	}

	collecting_aging_again = false;
}

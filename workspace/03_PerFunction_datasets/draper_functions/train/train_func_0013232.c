collect(int count, psbool emergency) {
  int i;
#if (S48_USE_STATIC_SPACE)
  psbool major_p = (count == (S48_GENERATIONS_COUNT - 1));
#else
  psbool major_p = (count == S48_GENERATIONS_COUNT);
#endif


#if (S48_ADJUST_WATER_MARK)
  aging_space_survival = 0;
  aging_space_before = 0;
  FOR_ALL_AREAS(generations[0].current_space->small_area,
		aging_space_before += (area->frontier - area->start));
#endif


  for (i = 0; i < count; i++) {
    swap(&generations[i]);
    generations[i].age_count++;

#if (BIBOP_LOG)
    s48_bibop_log("swapped current <-> other generation %i", i);
#endif
  }


  generations[count-1].self_count++;


  init_areas(count);


#if (S48_USE_REMEMBERED_SETS)
  for (i = 0; i < count; i++) {
    RemSet* rs; RemSet* nrs;
    FOR_ALL_AREAS(generations[i].other_space->small_area,
		  s48_trace_remset(area->remset));
    FOR_ALL_AREAS(generations[i].other_space->weaks_area,
		  s48_trace_remset(area->remset));


    FOR_ALL_AREAS(generations[i].other_space->large_area,
		  nrs = s48_make_remset();
		  rs = area->remset;
		  area->remset = nrs;
		  s48_trace_remset(rs);
		  s48_free_remset(rs);
		  );
  }
#endif


  for (i = count; i < S48_GENERATIONS_COUNT; i++) {

#if (BIBOP_LOG)
    s48_bibop_log("Tracing roots from current-space of generation %i\n", i);
#endif


    s48_trace_areas_roots(generations[i].current_space->small_area);
    s48_trace_areas_roots(generations[i].current_space->large_area);
  }

  s48_gc_root();


  do_gc();


  for (i = 0; i < S48_GENERATIONS_COUNT; i++) {
    clean_weak_pointers(generations[i].current_space->weaks_area);
  }

  s48_post_gc_cleanup(major_p, emergency);


  do_gc();

  for (i = 0; i < count; i++) {
    clear_space(generations[i].other_space);
    generations[i].last_size = calc_generation_size(&generations[i]);
  }


#if (S48_ADJUST_WATER_MARK)
  if (aging_space_before != 0)
    adjust_water_mark((float)aging_space_survival / aging_space_before);
#endif
  recreate_creation_space();

  gc_count++;
}

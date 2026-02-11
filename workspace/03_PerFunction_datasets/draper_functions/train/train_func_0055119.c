init_factor(F_PARAMETERS *p)
{

	p->ds_size = align_page(p->ds_size << 10);
	p->rs_size = align_page(p->rs_size << 10);


	p->young_size <<= 20;
	p->aging_size <<= 20;
	p->tenured_size <<= 20;
	p->code_size <<= 20;


	gc_off = true;


	early_init();

	if(p->image == NULL)
		p->image = default_image_path();

	srand(current_millis());
	init_ffi();
	init_stacks(p->ds_size,p->rs_size);
	load_image(p);
	init_c_io();
	init_signals();

	stack_chain = NULL;
	profiling_p = false;
	performing_gc = false;
	last_code_heap_scan = NURSERY;
	collecting_aging_again = false;

	userenv[CPU_ENV] = tag_object(from_char_string(FACTOR_CPU_STRING));
	userenv[OS_ENV] = tag_object(from_char_string(FACTOR_OS_STRING));
	userenv[CELL_SIZE_ENV] = tag_fixnum(sizeof(CELL));
	userenv[STACK_TRACES_ENV] = tag_boolean(p->stack_traces);


	gc_off = false;

	if(!stage2)
		do_stage1_init();
}

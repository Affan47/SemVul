game_init(state_t *s)
{
#ifdef __GNUC__
#  warning "Fixme: Use new VM instantiation code all over the place"
#endif
	reg_t game_obj;
	dstack_t *stack;

	stack = sm_allocate_stack(&s->seg_manager, VM_STACK_SIZE,
					      &s->stack_segment);
	s->stack_base = stack->entries;
	s->stack_top = s->stack_base + VM_STACK_SIZE;

	if (!script_instantiate(s, 0)) {
		sciprintf("game_init(): Could not instantiate script 0\n");
		return 1;
	}

	s->parser_valid = 0;
	s->parser_event = NULL_REG;

	s->synonyms = NULL;
	s->synonyms_nr = 0;


	if (!send_calls_allocated)
		send_calls = (calls_struct_t*)sci_calloc(sizeof(calls_struct_t), send_calls_allocated = 16);

	if (s->gfx_state && _reset_graphics_input(s))
		return 1;

	s->successor = NULL;
	s->status_bar_text = NULL;
	s->status_bar_foreground = 0;
	s->status_bar_background = s->resmgr->sci_version >= SCI_VERSION_01_VGA ? 255 : 15;

	sys_string_acquire(s->sys_strings, SYS_STRING_PARSER_BASE, "parser-base", MAX_PARSER_BASE);
	s->parser_base = make_reg(s->sys_strings_segment, SYS_STRING_PARSER_BASE);

	sci_get_current_time(&(s->game_start_time));
	memcpy(&(s->last_wait_time), &(s->game_start_time), sizeof(GTimeVal));


	s->debug_mode = 0x0;
	s->onscreen_console = 0;

	srand(time(NULL));


	game_obj = script_lookup_export(s, 0, 0);


	s->game_name = sci_strdup(obj_get_name(s, game_obj));

	if (!s->game_name) {
		sciprintf("Error: script.000, export 0 ("PREG") does not\n"
			  "  yield an object with a name -> sanity check failed\n",
			  PRINT_REG(game_obj));
		return 1;
	}

	sciprintf(" \"%s\" at "PREG"\n", s->game_name, PRINT_REG(game_obj));

	if (strlen((char *) s->game_name) >= MAX_GAMEDIR_SIZE) {

		s->game_name[MAX_GAMEDIR_SIZE - 1] = 0;
		sciprintf(" Designation too long; was truncated to \"%s\"\n", s->game_name);
	}

	s->game_obj = game_obj;


	s->parser_nodes[0].type = PARSE_TREE_NODE_LEAF;
	s->parser_nodes[0].content.value = 0;

	s->menubar = menubar_new();

	return 0;
}

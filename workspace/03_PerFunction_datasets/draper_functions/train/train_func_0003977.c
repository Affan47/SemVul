pform_push_task_scope(const struct vlltype&loc, char*name, bool is_auto)
{
      perm_string task_name = lex_strings.make(name);

      PTask*task;
      if (pform_cur_generate) {
	    task = new PTask(task_name, pform_cur_generate->lexical_scope,
	                     is_auto);
	    FILE_NAME(task, loc);

	    if (pform_cur_generate->tasks.find(task->pscope_name()) !=
	        pform_cur_generate->tasks.end()) {
		  cerr << task->get_fileline() << ": error: duplicate "
		          "definition for task '" << name << "' in '"
		       << pform_cur_module->mod_name() << "' (generate)."
		       << endl;
		  error_count += 1;
	    }
	    pform_cur_generate->tasks[task->pscope_name()] = task;
	    pform_cur_generate->lexical_scope = task;
      } else {
	    task = new PTask(task_name, lexical_scope,
                             is_auto);
	    FILE_NAME(task, loc);

	    if (pform_cur_module->tasks.find(task->pscope_name()) !=
	        pform_cur_module->tasks.end()) {
		  cerr << task->get_fileline() << ": error: duplicate "
		          "definition for task '" << name << "' in '"
		       << pform_cur_module->mod_name() << "'." << endl;
		  error_count += 1;
	    }
	    pform_cur_module->tasks[task->pscope_name()] = task;
	    lexical_scope = task;
      }

      return task;
}

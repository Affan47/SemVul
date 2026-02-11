qualifiers_match(exec_list *params)
{
   exec_list_iterator iter_a = parameters.iterator();
   exec_list_iterator iter_b = params->iterator();


   while (iter_a.has_next()) {
      ir_variable *a = (ir_variable *)iter_a.get();
      ir_variable *b = (ir_variable *)iter_b.get();


      if (a->read_only != b->read_only ||
	  !modes_match(a->mode, b->mode) ||
	  a->interpolation != b->interpolation ||
	  a->centroid != b->centroid) {


	 return a->name;
      }

      iter_a.next();
      iter_b.next();
   }
   return NULL;
}

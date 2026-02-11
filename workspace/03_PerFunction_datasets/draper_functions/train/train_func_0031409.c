script_exp_function_origin(void* closurev, const char* name, size_t namelen)
{
  Parser_closure* closure = static_cast<Parser_closure*>(closurev);
  Script_sections* ss = closure->script_options()->script_sections();
  Expression* origin = ss->find_memory_region_origin(name, namelen);

  if (origin == NULL)
    {
      gold_error(_("undefined memory region '%s' referenced "
		   "in ORIGIN expression"),
		 name);

      origin = script_exp_integer(0);
    }

  return origin;
}

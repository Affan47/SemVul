should_add_dynsym_entry(Symbol_table* symtab) const
{


  if (!this->in_real_elf())
    return false;


  if (this->needs_dynsym_entry())
    return true;


  if (parameters->options().gc_sections()
      && !parameters->options().shared()
      && this->source() == Symbol::FROM_OBJECT
      && !this->object()->is_dynamic())
    {
      Relobj* relobj = static_cast<Relobj*>(this->object());
      bool is_ordinary;
      unsigned int shndx = this->shndx(&is_ordinary);
      if (is_ordinary && shndx != elfcpp::SHN_UNDEF
          && !relobj->is_section_included(shndx)
          && !symtab->is_section_folded(relobj, shndx))
        return false;
    }


  if (!this->is_from_dynobj()
      && (parameters->options().in_dynamic_list(this->name())
	  || parameters->options().is_export_dynamic_symbol(this->name())))
    {
      if (!this->is_forced_local())
        return true;
      gold_warning(_("Cannot export local symbol '%s'"),
		   this->demangled_name().c_str());
      return false;
    }


  if (this->is_forced_local())
    return false;


  if (parameters->options().dynamic_list_data()
      && !this->is_from_dynobj()
      && this->type() == elfcpp::STT_OBJECT)
    return true;


  if ((parameters->options().dynamic_list_cpp_new()
       || parameters->options().dynamic_list_cpp_typeinfo())
      && !this->is_from_dynobj())
    {


      char* demangled_name = cplus_demangle(this->name(),
                                            DMGL_ANSI | DMGL_PARAMS);
      if (demangled_name == NULL)
        {

        }
      else if (parameters->options().dynamic_list_cpp_new()
               && (strprefix(demangled_name, "operator new")
                   || strprefix(demangled_name, "operator delete")))
        {
          free(demangled_name);
          return true;
        }
      else if (parameters->options().dynamic_list_cpp_typeinfo()
               && (strprefix(demangled_name, "typeinfo name for")
                   || strprefix(demangled_name, "typeinfo for")))
        {
          free(demangled_name);
          return true;
        }
      else
        free(demangled_name);
    }


  if ((parameters->options().export_dynamic() || parameters->options().shared())
      && !this->is_from_dynobj()
      && !this->is_undefined()
      && this->is_externally_visible())
    return true;

  return false;
}

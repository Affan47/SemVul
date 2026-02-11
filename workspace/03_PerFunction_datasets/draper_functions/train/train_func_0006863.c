pform_end_nature(const struct vlltype&loc)
{


      if (! nature_access) {
	    cerr << loc.text << ":" << loc.first_line << ": error: "
		 << "Missing access name for nature "
		 << nature_name << "." << endl;
	    error_count += 1;
	    nature_access = nature_name;
      }

      ivl_nature_s*tmp = new ivl_nature_s(nature_name, nature_access);
      FILE_NAME(tmp, loc);

      natures[nature_name] = tmp;


      if (ivl_nature_t dup_access_nat = access_function_nature[nature_access]) {
	    cerr << tmp->get_fileline() << ": error: "
		 << "Access function name " << nature_access
		 << " is already used by nature " << dup_access_nat->name()
		 << " declared at " << dup_access_nat->get_fileline()
		 << "." << endl;
	    error_count += 1;
      }


      access_function_nature[nature_access] = tmp;

      nature_name = perm_string();
      nature_access = perm_string();
}

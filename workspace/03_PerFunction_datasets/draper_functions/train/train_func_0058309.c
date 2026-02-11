pform_set_default_nettype(NetNet::Type type,
			       const char*file, unsigned lineno)
{
      pform_default_nettype = type;

      if (pform_cur_module) {
	    cerr << file<<":"<<lineno << ": error: "
		 << "`default_nettype directives must appear" << endl;
	    cerr << file<<":"<<lineno << ":      : "
		 << "outside module definitions. The containing" << endl;
	    cerr << file<<":"<<lineno << ":      : "
		 << "module " << pform_cur_module->mod_name()
		 << " starts on line "
		 << pform_cur_module->get_fileline() << "." << endl;
	    error_count += 1;
      }
}

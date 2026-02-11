top(Node *n) {
  module_name = Getattr(n, "name");
  String *cxx_filename = Getattr(n, "outfile");
  String *cl_filename = NewString("");

  swig_package = unique_swig_package ? NewStringf("swig.%s", module_name) : NewString("swig");

  Printf(cl_filename, "%s%s.cl", SWIG_output_directory(), module_name);

  f_cl = NewFile(cl_filename, "w", SWIG_output_files());
  if (!f_cl) {
    Printf(stderr, "Unable to open %s for writing\n", cl_filename);
    SWIG_exit(EXIT_FAILURE);
  }

  Generate_Wrapper = CPlusPlus || CWrap;

  if (Generate_Wrapper) {
    f_begin = NewFile(cxx_filename, "w", SWIG_output_files());
    if (!f_begin) {
      Close(f_cl);
      Delete(f_cl);
      Printf(stderr, "Unable to open %s for writing\n", cxx_filename);
      SWIG_exit(EXIT_FAILURE);
    }
  } else
    f_begin = NewString("");

  f_runtime = NewString("");
  f_cxx_header = f_runtime;
  f_cxx_wrapper = NewString("");

  Swig_register_filebyname("header", f_cxx_header);
  Swig_register_filebyname("wrapper", f_cxx_wrapper);
  Swig_register_filebyname("begin", f_begin);
  Swig_register_filebyname("runtime", f_runtime);
  Swig_register_filebyname("lisp", f_clwrap);
  Swig_register_filebyname("lisphead", f_cl);

  Swig_banner(f_begin);

  Printf(f_runtime, "\n");
  Printf(f_runtime, "#define SWIGALLEGROCL\n");
  Printf(f_runtime, "\n");

  Swig_banner_target_lang(f_cl, ";;");

  Printf(f_cl, "\n"
	 "(defpackage :%s\n"
	 "  (:use :common-lisp :ff :excl)\n"
	 "  (:export #:*swig-identifier-converter* #:*swig-module-name*\n"
	 "           #:*void* #:*swig-export-list*))\n"
	 "(in-package :%s)\n\n"
	 "(eval-when (:compile-toplevel :load-toplevel :execute)\n"
	 "  (defparameter *swig-identifier-converter* '%s)\n"
	 "  (defparameter *swig-module-name* :%s))\n\n", swig_package, swig_package, identifier_converter, module_name);
  Printf(f_cl, "(defpackage :%s\n" "  (:use :common-lisp :%s :ff :excl))\n\n", module_name, swig_package);

  Printf(f_clhead, "(in-package :%s)\n", module_name);


  Language::top(n);


#ifdef ALLEGROCL_TYPE_DEBUG
  dump_linked_types(stderr);
#endif
  emit_linked_types();

  Printf(f_clwrap, "\n(cl::in-package :%s)\n", swig_package);
  Printf(f_clwrap, "\n(macrolet ((swig-do-export ()\n");
  Printf(f_clwrap, "                 `(dolist (s ',*swig-export-list*)\n");
  Printf(f_clwrap, "                    (apply #'export s))))\n");
  Printf(f_clwrap, "   (swig-do-export))\n");
  Printf(f_clwrap, "\n(setq *swig-export-list* nil)\n");

  Printf(f_cl, "%s\n", f_clhead);
  Printf(f_cl, "%s\n", f_clwrap);

  Close(f_cl);
  Delete(f_cl);
  Delete(f_clhead);
  Delete(f_clwrap);

  Dump(f_runtime, f_begin);
  Printf(f_begin, "%s\n", f_cxx_wrapper);

  Close(f_begin);
  Delete(f_runtime);
  Delete(f_begin);
  Delete(f_cxx_wrapper);


  return SWIG_OK;
}

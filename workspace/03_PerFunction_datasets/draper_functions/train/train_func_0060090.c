java_handle_option (size_t scode, const char *arg, int value,
		    int kind ATTRIBUTE_UNUSED, location_t loc ATTRIBUTE_UNUSED,
		    const struct cl_option_handlers *handlers ATTRIBUTE_UNUSED)
{
  enum opt_code code = (enum opt_code) scode;

  switch (code)
    {
    case OPT_I:
      jcf_path_include_arg (arg);
      break;

    case OPT_M:
      jcf_dependency_init (1);
      dependency_tracking |= DEPEND_ENABLE;
      break;

    case OPT_MD_:
      jcf_dependency_init (1);
      dependency_tracking |= DEPEND_SET_FILE | DEPEND_ENABLE;
      break;

    case OPT_MF:
      jcf_dependency_set_dep_file (arg);
      dependency_tracking |= DEPEND_FILE_ALREADY_SET;
      break;

    case OPT_MM:
      jcf_dependency_init (0);
      dependency_tracking |= DEPEND_ENABLE;
      break;

    case OPT_MMD_:
      jcf_dependency_init (0);
      dependency_tracking |= DEPEND_SET_FILE | DEPEND_ENABLE;
      break;

    case OPT_MP:
      jcf_dependency_print_dummies ();
      break;

    case OPT_MT:
      jcf_dependency_set_target (arg);
      dependency_tracking |= DEPEND_TARGET_SET;
      break;

    case OPT_Wall:
      flag_wall = value;


      warn_unused = value;
      break;

    case OPT_fenable_assertions_:
      add_enable_assert (arg, value);
      break;

    case OPT_fenable_assertions:
      add_enable_assert ("", value);
      break;

    case OPT_fdisable_assertions_:
      add_enable_assert (arg, !value);
      break;

    case OPT_fdisable_assertions:
      add_enable_assert ("", !value);
      break;

    case OPT_fassume_compiled_:
      add_assume_compiled (arg, !value);
      break;

    case OPT_fassume_compiled:
      add_assume_compiled ("", !value);
      break;

    case OPT_fbootclasspath_:
      jcf_path_bootclasspath_arg (arg);
      break;

    case OPT_faux_classpath:
    case OPT_fclasspath_:
      jcf_path_classpath_arg (arg);
      break;

    case OPT_fcompile_resource_:
      resource_name = arg;
      break;

    case OPT_fdump_:
      if (!dump_switch_p (arg))
	return false;
      break;

    case OPT_fencoding_:

      break;

    case OPT_fextdirs_:
      jcf_path_extdirs_arg (arg);
      break;

    case OPT_foutput_class_dir_:

      break;

    case OPT_version:
      v_flag = 1;
      break;

    case OPT_fsource_filename_:
      java_read_sourcefilenames (arg);
      break;

    default:
      if (cl_options[code].flags & CL_Java)
	break;
      gcc_unreachable ();
    }

  return true;
}

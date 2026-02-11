gt_readjoiner_runner(int argc, const char **argv, int parsed_args,
                         void *tool_arguments, GtError *err)
{
  GtToolbox *readjoiner_toolbox = tool_arguments;
  GtToolfunc toolfunc;
  GtTool *tool = NULL;
  int had_err = 0;
  char **nargv = NULL;

  gt_error_check(err);
  gt_assert(readjoiner_toolbox);


  if (!gt_toolbox_has_tool(readjoiner_toolbox, argv[parsed_args])) {
    gt_error_set(err, "readjoiner tool '%s' not found; option -help lists "
                      "possible tools", argv[parsed_args]);
    had_err = -1;
  }


  if (!had_err) {
    if (!(toolfunc = gt_toolbox_get(readjoiner_toolbox, argv[parsed_args]))) {
      tool = gt_toolbox_get_tool(readjoiner_toolbox, argv[parsed_args]);
      gt_assert(tool);
    }
    nargv = gt_cstr_array_prefix_first(argv + parsed_args,
                                       gt_error_get_progname(err));
    gt_error_set_progname(err, nargv[0]);
    if (toolfunc)
      had_err = toolfunc(argc - parsed_args, (const char**) nargv, err);
    else
      had_err = gt_tool_run(tool, argc - parsed_args, (const char**) nargv,
                            err);
  }


  gt_cstr_array_delete(nargv);

  return had_err;
}

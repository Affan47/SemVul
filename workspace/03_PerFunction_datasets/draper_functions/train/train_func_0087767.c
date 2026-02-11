cb_arg_init (poptContext __unused__ ctx,
	     enum poptCallbackReason __unused__ reason,
	     const struct poptOption *opt, const char *arg,
	     CallbackParams *params)
{
	switch (opt->val) {

	case ARG_FILENAME:
		params->p.r = set_filename_action (&gp_params, arg);
		break;
	case ARG_FOLDER:
		params->p.r = set_folder_action (&gp_params, arg);
		break;

	case ARG_FORCE_OVERWRITE:
		gp_params.flags |= FLAGS_FORCE_OVERWRITE;
		break;
	case ARG_NEW:
		gp_params.flags |= FLAGS_NEW;
		break;
	case ARG_KEEP:
		gp_params.flags |= FLAGS_KEEP;
		break;
	case ARG_NO_KEEP:
		gp_params.flags &= ~FLAGS_KEEP;
		break;

	case ARG_NO_RECURSE:
		gp_params.flags &= ~FLAGS_RECURSE;
		break;
	case ARG_RECURSE:
		gp_params.flags |= FLAGS_RECURSE;
		break;

	case ARG_MODEL:
		gp_log (GP_LOG_DEBUG, "main", "Processing 'model' "
			"option ('%s')...", arg);
		params->p.r = action_camera_set_model (&gp_params, arg);
		break;
	case ARG_PORT:
		gp_log (GP_LOG_DEBUG, "main", "Processing 'port' "
			"option ('%s')...", arg);
		params->p.r = action_camera_set_port (&gp_params, arg);
		break;
	case ARG_SPEED:
		params->p.r = action_camera_set_speed (&gp_params, atoi (arg));
		break;

	case ARG_QUIET:
		gp_params.flags |= FLAGS_QUIET;
		break;

	case ARG_RESET_INTERVAL:
		gp_params.flags |= FLAGS_RESET_CAPTURE_INTERVAL;
		break;

	case ARG_HOOK_SCRIPT:
		do {
			const size_t sz = strlen(arg);
			char *copy = malloc(sz+1);
			if (!copy) {
				perror("malloc error");
				exit (EXIT_FAILURE);
			}
			gp_params.hook_script = strcpy(copy, arg);

			if (0!=gp_params_run_hook(&gp_params, "init", NULL)) {
				fprintf(stderr,
					"Hook script \"%s\" init failed. Aborting.\n",
					gp_params.hook_script);
				exit(3);
			}
		} while (0);
		break;

	case ARG_STDOUT:
		gp_params.flags |= FLAGS_QUIET | FLAGS_STDOUT;
		break;
	case ARG_STDOUT_SIZE:
		gp_params.flags |= FLAGS_QUIET | FLAGS_STDOUT
			| FLAGS_STDOUT_SIZE;
		break;

	case ARG_CAPTURE_FRAMES:
		glob_frames = atoi(arg);
		break;
	case ARG_CAPTURE_INTERVAL:
		glob_interval = atoi(arg);
		break;
	case ARG_CAPTURE_BULB:
		glob_bulblength = atoi(arg);
		break;

	case ARG_VERSION:
		params->p.r = print_version_action (&gp_params);
		break;

	default:
		break;
	}
}

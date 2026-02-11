_set_rec(int *start, int argc, char *argv[],
		    List name_list,
		    slurmdb_association_rec_t *assoc,
		    uint16_t *classification)
{
	int i;
	int set = 0;
	int end = 0;
	int command_len = 0;
	int option = 0;

	for (i=(*start); i<argc; i++) {
		end = parse_option_end(argv[i]);
		if (!end)
			command_len=strlen(argv[i]);
		else {
			command_len=end-1;
			if (argv[i][end] == '=') {
				option = (int)argv[i][end-1];
				end++;
			}
		}

		if (!strncasecmp(argv[i], "Where", MAX(command_len, 5))) {
			i--;
			break;
		} else if (!end && !strncasecmp(argv[i], "set",
					       MAX(command_len, 3))) {
			continue;
		} else if (!end
			  || !strncasecmp(argv[i], "Names",
					   MAX(command_len, 1))
			  || !strncasecmp(argv[i], "Clusters",
					   MAX(command_len, 3))) {
			if (name_list)
				slurm_addto_char_list(name_list,
						      argv[i]+end);
		} else if (!strncasecmp(argv[i], "Classification",
					 MAX(command_len, 3))) {
			if (classification) {
				*classification =
					str_2_classification(argv[i]+end);
				if (*classification)
					set = 1;
			}
		} else if (!strncasecmp(argv[i], "GrpCPURunMins",
					 MAX(command_len, 7))) {
			exit_code=1;
			fprintf(stderr, "GrpCPURunMins is not a valid option "
				"for the root association of a cluster.\n");
			break;
		} else if (!strncasecmp(argv[i], "GrpCPUMins",
					 MAX(command_len, 7))) {
			exit_code=1;
			fprintf(stderr, "GrpCPUMins is not a valid option "
				"for the root association of a cluster.\n");
			break;
		} else if (!strncasecmp(argv[i], "GrpWall",
					 MAX(command_len, 4))) {
			exit_code=1;
			fprintf(stderr, "GrpWall is not a valid option "
				"for the root association of a cluster.\n");
		} else if (!assoc ||
			  (assoc && !(set = sacctmgr_set_association_rec(
					      assoc, argv[i], argv[i]+end,
					      command_len, option)))) {
			exit_code=1;
			fprintf(stderr, " Unknown option: %s\n"
				" Use keyword 'where' to modify condition\n",
				argv[i]);
		}
	}
	(*start) = i;

	return set;

}

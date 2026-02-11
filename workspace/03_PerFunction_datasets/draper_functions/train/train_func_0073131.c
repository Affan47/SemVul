open_report(input_options *options)
{

	output_report *report;

	if((report=MALLOC(output_report))==NULL)
	{
		fprintf(stderr,"ERROR: FAILED TO ALLOCATE MEMORY\n");
		exit(1);
	}

	if(options->save_output)
	{
		if(!(report->report_file=fopen(options->outfile,"w+")))
		{
			fprintf(stderr,"ERROR: CANNOT CREATE REPORT OUTPUT FILE: %s\n",options->outfile);
			exit(1);
		}
	}
	else report->report_file=NULL;

	report->options=options;

	report->print_init=(void *)&print_init;
	report->print_end=(void *)&print_end;

	if(options->middle_op)
		report->print_middle=(void *)&print_middle;
	else
		report->print_middle=(void *)&void_print_middle;

	if(options->print_iter)
		report->print_iteration=(void *)&print_iteration;
	else
		report->print_iteration=(void *)&void_print_iteration;
	if(options->paranoid_leve==4)
	{
		report->print_paranoid=(void *)&print_paranoid;
		report->print_paranoid_move=(void *)&print_paranoid_move;
		report->print_paranoid_eval=(void *)&print_paranoid_eval;
		report->print_paranoid_all=(void *)&print_paranoid_all;
	}
	if(options->paranoid_leve==3)
	{
		report->print_paranoid=(void *)&print_paranoid;
		report->print_paranoid_move=(void *)&print_paranoid_move;
		report->print_paranoid_eval=(void *)&print_paranoid_eval;
		report->print_paranoid_all=(void *)&void_print_paranoid_all;
	}
	else{
		if(options->paranoid_leve==2)
		{
			report->print_paranoid=(void *)&print_paranoid;
			report->print_paranoid_move=(void *)&print_paranoid_move;
			report->print_paranoid_eval=(void *)&void_print_paranoid_eval;
			report->print_paranoid_all=(void *)&void_print_paranoid_all;
		}
		else{
			if(options->paranoid_leve==1)
			{
				report->print_paranoid=(void *)&print_paranoid;
				report->print_paranoid_move=(void *)&void_print_paranoid_move;
				report->print_paranoid_eval=(void *)&void_print_paranoid_eval;
				report->print_paranoid_all=(void *)&void_print_paranoid_all;
			}
			else{
				if(options->paranoid_leve==0)
				{
					report->print_paranoid=(void *)&void_print_paranoid;
					report->print_paranoid_move=(void *)&void_print_paranoid_move;
					report->print_paranoid_eval=(void *)&void_print_paranoid_eval;
					report->print_paranoid_all=(void *)&void_print_paranoid_all;
				}
			}
		}
	}
	return(report);
}

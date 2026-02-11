cloog_input_dump_cloog(FILE *file, CloogInput *input, CloogOptions *opt)
{
        int i, num_statements;
        CloogUnionDomain *ud = input->ud;
        CloogNamedDomainList *ndl = ud->domain;

        fprintf(file,
                "# CLooG -> CLooG\n"
                "# This is an automatic dump of a CLooG input file from a "
                "CloogInput data\n"
                "# structure.\n\n");


        if (opt->language == CLOOG_LANGUAGE_FORTRAN) {
                fprintf(file, "# Language: FORTRAN\n");
                fprintf(file, "f\n\n");
        } else {
                fprintf(file, "# Language: C\n");
                fprintf(file, "c\n\n");
        }


        fprintf(file, "# Context:\n");
        cloog_domain_print_constraints(file, input->context, 1);

	print_names(file, ud, CLOOG_PARAM, "Parameter");


        i = 0;
        while (ndl != NULL) {
        	i++;
        	ndl = ndl->next;
        }
        num_statements = i;
        fprintf(file, "\n# Statement number:\n%d\n\n", num_statements);


        i = 1;
        ndl = ud->domain;
        while (ndl != NULL) {
                fprintf(file, "# Iteration domain of statement %d (%s).\n", i,
                        ndl->name);

                cloog_domain_print_constraints(file, ndl->domain, 1);
                fprintf(file,"\n0 0 0 # For future options.\n\n");

                i++;
                ndl = ndl->next;
        }

	print_names(file, ud, CLOOG_ITER, "Iterator");


        if (!ud->domain || !ud->domain->scattering) {
                fprintf(file, "# No scattering functions.\n0\n\n");
                return;
        }


        fprintf(file,
                "# --------------------- SCATTERING --------------------\n");

        fprintf(file, "%d # Scattering functions\n", num_statements);

        i = 1;
        ndl = ud->domain;
        while (ndl != NULL) {
                fprintf(file, "\n# Scattering of statement %d (%s).\n", i,
                        ndl->name);

                cloog_scattering_print_constraints(file, ndl->scattering);

                i++;
                ndl = ndl->next;
        }

	print_names(file, ud, CLOOG_SCAT, "Scattering dimension");
}

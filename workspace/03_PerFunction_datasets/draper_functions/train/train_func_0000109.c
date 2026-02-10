pretty_process_dot(const char *infile, bool file_is_expr, const char *outfile,
		   ErrorHandler *errh)
{
    RouterT *r = read_router(infile, file_is_expr, errh);
    if (!r)
	return;


    FILE *outf = open_output_file(outfile, errh);
    if (!outf) {
	delete r;
	return;
    }


    fprintf(outf, "digraph clickrouter {\n\
  node [shape=record,height=.1]\n\
  edge [arrowhead=normal,arrowtail=none,tailclip=false]\n");


    for (RouterT::const_iterator n = r->begin_elements(); n != r->end_elements(); n++) {
	fprintf(outf, "  \"%s\" [label=\"", n->name_c_str());
	if (n->ninputs() || n->noutputs())
	    fprintf(outf, "{");
	if (n->ninputs()) {
	    fprintf(outf, "{");
	    for (int i = 0; i < n->ninputs(); i++)
		fprintf(outf, (i ? "|<i%d>" : "<i%d>"), i);
	    fprintf(outf, "}|");
	}
	fputs(n->type_name_c_str(), outf);
	if (n->noutputs()) {
	    fprintf(outf, "|{");
	    for (int i = 0; i < n->noutputs(); i++)
		fprintf(outf, (i ? "|<o%d>" : "<o%d>"), i);
	    fprintf(outf, "}");
	}
	if (n->ninputs() || n->noutputs())
	    fprintf(outf, "}");
	fprintf(outf, "\"];\n");
    }


    const Vector<ConnectionT> &conns = r->connections();
    for (const ConnectionT *c = conns.begin(); c != conns.end(); c++)
	fprintf(outf, "  \"%s\":o%d -> \"%s\":i%d;\n",
		c->from_element()->name_c_str(), c->from_port(),
		c->to_element()->name_c_str(), c->to_port());

    fprintf(outf, "}\n");


    if (outf != stdout)
	fclose(outf);
    delete r;
}

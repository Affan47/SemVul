DumpFatals() {
    for (unsigned int x = 0; x < fatalqueue.size(); x++) {
		if (glob_linewrap)
			fprintf(stderr, "%s", InLineWrap("FATAL: " + fatalqueue[x],
											 7, 80).c_str());
		else
			fprintf(stderr, "FATAL: %s\n", fatalqueue[x].c_str());
    }
}

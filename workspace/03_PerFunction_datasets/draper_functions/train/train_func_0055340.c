init_dict() {

    string s = (macros.find("bullet") != macros.end()) ?
	"bullet;" : "\"\\(bu\";\n";

    s.insert(0,"new grap_internal_default invis ");
    include_string(&s, 0, GINTERNAL);
    defline = new line();
    the_graph->lines["grap_internal_default"] = defline;

    defcoord = new coord;
    the_graph->coords["grap.internal.default"] = defcoord;
    for ( int i = 0 ; i < 4; i++) {
	the_graph->base->tickdef[i].c = defcoord;
	the_graph->base->griddef[i].c = defcoord;
    }
    nlines = 0;
}

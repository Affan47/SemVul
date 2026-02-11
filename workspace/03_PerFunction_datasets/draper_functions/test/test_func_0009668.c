kc_do_printdot_subgraph_prologue__nocasestring
#ifdef KC_USE_PROTOTYPES
(FILE *kc_f, nocasestring kc_p, char *kc_root, char *kc_edge_attributes, boolean kc_phy_labels, boolean kc_use_ctxt)
#else
(kc_f, kc_p, kc_root, kc_edge_attributes, kc_phy_labels, kc_use_ctxt) FILE *kc_f; nocasestring kc_p; char *kc_root; char *kc_edge_attributes; boolean kc_phy_labels; boolean kc_use_ctxt;
#endif
{	if (!kc_f) kc_f = stdout;
	(void)fprintf(kc_f, "/*subgraph*/ {\n");
	if (kc_root) {
		(void)fprintf(kc_f, "\"%s\" [shape=ellipse", kc_root);
		if (kc_edge_attributes && (strlen(kc_edge_attributes) > 0)) {
			(void)fprintf(kc_f, ", %s", kc_edge_attributes);
		}
		if (kc_phy_labels) {
			(void)fprintf(kc_f, ", label=\"%s\\n%s\"", kc_root, kc_PhylumInfo[kc_phylum_nocasestring].name);
		}
		(void)fprintf(kc_f, "];\n");
		(void)fprintf(kc_f, "\"%s\" ->", kc_root);
		kc_do_printdot_id_of__nocasestring(kc_f, kc_p, kc_use_ctxt, 0, 0);
		if (kc_edge_attributes && (strlen(kc_edge_attributes) > 0)) {
			(void)fprintf(kc_f, "[%s]", kc_edge_attributes);
		}
		(void)fprintf(kc_f, ";\n");
	}
}

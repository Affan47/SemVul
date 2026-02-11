gp_push_func (gboolean vararg, gboolean arguments, gboolean extradict, gboolean never_subst)
{
	GelETree * tree;
	GelETree * val;
	GSList * list = NULL;
	GSList * elist = NULL;
	int argnum = 0;
	gboolean local_all = FALSE;
	GSList *local_idents = NULL;

	val = gel_stack_pop (&gel_parsestack);
	if G_UNLIKELY (val == NULL)
		return FALSE;

	if (gel_get_local_node (val, TRUE ,
				&local_all, &local_idents) == 2) {
		gel_errorout ("%s", _("ERROR: local statement not the first statement in function definition"));
		gel_freetree (val);
		g_slist_free (local_idents);
		return FALSE;
	}

	if (extradict) {
		for (;;) {
			tree = gel_stack_pop (&gel_parsestack);
			if (tree != NULL &&
			    tree->type == GEL_EXPRLIST_START_NODE) {
				gel_freetree (tree);
				break;
			}


			if G_UNLIKELY (tree == NULL ||
				       tree->type != GEL_IDENTIFIER_NODE) {
				if (tree != NULL) gel_freetree(tree);
				g_slist_free (elist);
				g_slist_free (local_idents);
				return FALSE;
			}
			elist = g_slist_prepend (elist, tree->id.id);
			gel_freetree (tree);
		}
	}

	if (arguments) {
		for (;;) {
			tree = gel_stack_pop (&gel_parsestack);
			if (tree != NULL &&
			    tree->type == GEL_EXPRLIST_START_NODE) {
				gel_freetree (tree);
				break;
			}


			if G_UNLIKELY (tree == NULL ||
				       tree->type != GEL_IDENTIFIER_NODE) {
				if (tree != NULL) gel_freetree(tree);
				g_slist_free (list);
				g_slist_free (elist);
				g_slist_free (local_idents);
				return FALSE;
			}
			list = g_slist_prepend (list, tree->id.id);
			gel_freetree (tree);
			argnum++;
		}
	}

	GEL_GET_NEW_NODE(tree);

	tree->type = GEL_FUNCTION_NODE;
	tree->func.func = d_makeufunc(NULL,val,list,argnum, NULL);
	tree->func.func->context = -1;
	tree->func.func->vararg = vararg;
	tree->func.func->local_all = local_all ? 1 : 0;
	tree->func.func->local_idents = local_idents;
	tree->func.func->never_on_subst_list = never_subst ? 1 : 0;

	if (never_subst) {
		tree->func.func->built_subst_dict = 1;
		tree->func.func->subst_dict = elist;
	}

	gel_stack_push(&gel_parsestack,tree);

	return TRUE;
}

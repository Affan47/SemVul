ctf_typealias_visit(FILE *fd, int depth, struct declaration_scope *scope,
		struct ctf_node *target, struct ctf_node *alias,
		struct ctf_trace *trace)
{
	struct bt_declaration *type_declaration;
	struct ctf_node *node;
	GQuark dummy_id;
	GQuark alias_q;
	int err;


	if (bt_list_empty(&target->u.typealias_target.type_declarators))
		node = NULL;
	else
		node = _bt_list_first_entry(&target->u.typealias_target.type_declarators,
				struct ctf_node, siblings);
	type_declaration = ctf_type_declarator_visit(fd, depth,
		target->u.typealias_target.type_specifier_list,
		&dummy_id, node,
		scope, NULL, trace);
	if (!type_declaration) {
		fprintf(fd, "[error] %s: problem creating type declaration\n", __func__);
		err = -EINVAL;
		goto error;
	}


	if (type_declaration->id == CTF_TYPE_UNTAGGED_VARIANT) {
		fprintf(fd, "[error] %s: typedef of untagged variant is not permitted.\n", __func__);
		bt_declaration_unref(type_declaration);
		return -EPERM;
	}


	if (dummy_id != 0) {
		fprintf(fd, "[error] %s: expecting empty identifier\n", __func__);
		err = -EINVAL;
		goto error;
	}


	node = _bt_list_first_entry(&alias->u.typealias_alias.type_declarators,
				struct ctf_node, siblings);
	alias_q = create_typealias_identifier(fd, depth,
			alias->u.typealias_alias.type_specifier_list, node);
	err = bt_register_declaration(alias_q, type_declaration, scope);
	if (err)
		goto error;
	bt_declaration_unref(type_declaration);
	return 0;

error:
	if (type_declaration) {
		type_declaration->declaration_free(type_declaration);
	}
	return err;
}

policydb_index(struct policydb *p)
{
	int i, rc;

	printk(KERN_DEBUG "SELinux:  %d users, %d roles, %d types, %d bools",
	       p->p_users.nprim, p->p_roles.nprim, p->p_types.nprim, p->p_bools.nprim);
	if (p->mls_enabled)
		printk(", %d sens, %d cats", p->p_levels.nprim,
		       p->p_cats.nprim);
	printk("\n");

	printk(KERN_DEBUG "SELinux:  %d classes, %d rules\n",
	       p->p_classes.nprim, p->te_avtab.nel);

#ifdef DEBUG_HASHES
	avtab_hash_eval(&p->te_avtab, "rules");
	symtab_hash_eval(p->symtab);
#endif

	rc = -ENOMEM;
	p->class_val_to_struct =
		kmalloc(p->p_classes.nprim * sizeof(*(p->class_val_to_struct)),
			GFP_KERNEL);
	if (!p->class_val_to_struct)
		goto out;

	rc = -ENOMEM;
	p->role_val_to_struct =
		kmalloc(p->p_roles.nprim * sizeof(*(p->role_val_to_struct)),
			GFP_KERNEL);
	if (!p->role_val_to_struct)
		goto out;

	rc = -ENOMEM;
	p->user_val_to_struct =
		kmalloc(p->p_users.nprim * sizeof(*(p->user_val_to_struct)),
			GFP_KERNEL);
	if (!p->user_val_to_struct)
		goto out;


	rc = -ENOMEM;
	p->type_val_to_struct_array = flex_array_alloc(sizeof(struct type_datum *),
						       p->p_types.nprim,
						       GFP_KERNEL | __GFP_ZERO);
	if (!p->type_val_to_struct_array)
		goto out;

	rc = flex_array_prealloc(p->type_val_to_struct_array, 0,
				 p->p_types.nprim, GFP_KERNEL | __GFP_ZERO);
	if (rc)
		goto out;

	rc = cond_init_bool_indexes(p);
	if (rc)
		goto out;

	for (i = 0; i < SYM_NUM; i++) {
		rc = -ENOMEM;
		p->sym_val_to_name[i] = flex_array_alloc(sizeof(char *),
							 p->symtab[i].nprim,
							 GFP_KERNEL | __GFP_ZERO);
		if (!p->sym_val_to_name[i])
			goto out;

		rc = flex_array_prealloc(p->sym_val_to_name[i],
					 0, p->symtab[i].nprim,
					 GFP_KERNEL | __GFP_ZERO);
		if (rc)
			goto out;

		rc = hashtab_map(p->symtab[i].table, index_f[i], p);
		if (rc)
			goto out;
	}
	rc = 0;
out:
	return rc;
}

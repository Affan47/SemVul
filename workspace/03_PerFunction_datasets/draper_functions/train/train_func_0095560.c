recordDependencyOnSingleRelExpr(const ObjectAddress *depender,
								Node *expr, Oid relId,
								DependencyType behavior,
								DependencyType self_behavior)
{
	find_expr_references_context context;
	RangeTblEntry rte;

	context.addrs = new_object_addresses();


	MemSet(&rte, 0, sizeof(rte));
	rte.type = T_RangeTblEntry;
	rte.rtekind = RTE_RELATION;
	rte.relid = relId;

	context.rtables = list_make1(list_make1(&rte));


	find_expr_references_walker(expr, &context);


	eliminate_duplicate_dependencies(context.addrs);


	if (behavior != self_behavior && context.addrs->numrefs > 0)
	{
		ObjectAddresses *self_addrs;
		ObjectAddress *outobj;
		int			oldref,
					outrefs;

		self_addrs = new_object_addresses();

		outobj = context.addrs->refs;
		outrefs = 0;
		for (oldref = 0; oldref < context.addrs->numrefs; oldref++)
		{
			ObjectAddress *thisobj = context.addrs->refs + oldref;

			if (thisobj->classId == RelationRelationId &&
				thisobj->objectId == relId)
			{

				add_exact_object_address(thisobj, self_addrs);
			}
			else
			{

				*outobj = *thisobj;
				outobj++;
				outrefs++;
			}
		}
		context.addrs->numrefs = outrefs;


		recordMultipleDependencies(depender,
								   self_addrs->refs, self_addrs->numrefs,
								   self_behavior);

		free_object_addresses(self_addrs);
	}


	recordMultipleDependencies(depender,
							   context.addrs->refs, context.addrs->numrefs,
							   behavior);

	free_object_addresses(context.addrs);
}

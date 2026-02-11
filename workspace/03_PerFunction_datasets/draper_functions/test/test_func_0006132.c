coerce_type_typmod(Node *node, Oid targetTypeId, int32 targetTypMod,
				   CoercionForm cformat, bool isExplicit,
				   bool hideInputCoercion)
{
	Oid			funcId;


	if (targetTypMod < 0 || targetTypMod == exprTypmod(node))
		return node;

	funcId = find_typmod_coercion_function(targetTypeId);

	if (OidIsValid(funcId))
	{

		if (hideInputCoercion)
			hide_coercion_node(node);

		node = build_coercion_expression(node, funcId,
										 targetTypeId, targetTypMod,
										 cformat, isExplicit);
	}

	return node;
}

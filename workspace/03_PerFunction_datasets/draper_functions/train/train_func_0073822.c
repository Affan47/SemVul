is_projection_capable_plan(Plan *plan)
{

	switch (nodeTag(plan))
	{
		case T_Hash:
		case T_Material:
		case T_Sort:
		case T_Unique:
		case T_SetOp:
		case T_Limit:
		case T_Append:
			return false;
		default:
			break;
	}
	return true;
}

ExecSupportsMarkRestore(Path *pathnode)
{


	switch (pathnode->pathtype)
	{
		case T_IndexScan:
		case T_IndexOnlyScan:
		case T_Material:
		case T_Sort:
			return true;

		case T_CustomScan:
			Assert(IsA(pathnode, CustomPath));
			if (((CustomPath *) pathnode)->flags & CUSTOMPATH_SUPPORT_MARK_RESTORE)
				return true;
			return false;

		case T_Result:


			Assert(IsA(pathnode, ResultPath));
			return false;

		default:
			break;
	}

	return false;
}

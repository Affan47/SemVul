ctf_visitor_type_specifier(FILE *fd, int depth, struct ctf_node *node)
{
	int ret;

	switch (node->u.type_specifier.type) {
	case TYPESPEC_VOID:
	case TYPESPEC_CHAR:
	case TYPESPEC_SHORT:
	case TYPESPEC_INT:
	case TYPESPEC_LONG:
	case TYPESPEC_FLOAT:
	case TYPESPEC_DOUBLE:
	case TYPESPEC_SIGNED:
	case TYPESPEC_UNSIGNED:
	case TYPESPEC_BOOL:
	case TYPESPEC_COMPLEX:
	case TYPESPEC_IMAGINARY:
	case TYPESPEC_CONST:
	case TYPESPEC_ID_TYPE:
		break;
	case TYPESPEC_FLOATING_POINT:
	case TYPESPEC_INTEGER:
	case TYPESPEC_STRING:
	case TYPESPEC_STRUCT:
	case TYPESPEC_VARIANT:
	case TYPESPEC_ENUM:
		node->u.type_specifier.node->parent = node;
		ret = ctf_visitor_parent_links(fd, depth + 1, node->u.type_specifier.node);
		if (ret)
			return ret;
		break;

	case TYPESPEC_UNKNOWN:
	default:
		fprintf(fd, "[error] %s: unknown type specifier %d\n", __func__,
			(int) node->u.type_specifier.type);
		return -EINVAL;
	}
	return 0;
}

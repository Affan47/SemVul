cb_build_binary_op (cb_tree x, int op, cb_tree y)
{
	struct cb_binary_op	*p;
	enum cb_category	category = CB_CATEGORY_UNKNOWN;

	switch (op) {
	case '+':
	case '-':
	case '*':
	case '/':
	case '^':

		if (CB_TREE_CLASS (x) == CB_CLASS_POINTER ||
		    CB_TREE_CLASS (y) == CB_CLASS_POINTER) {
			category = CB_CATEGORY_DATA_POINTER;
			break;
		}
		x = cb_check_numeric_value (x);
		y = cb_check_numeric_value (y);
		if (x == cb_error_node || y == cb_error_node) {
			return cb_error_node;
		}
		category = CB_CATEGORY_NUMERIC;
		break;

	case '=':
	case '~':
	case '<':
	case '>':
	case '[':
	case ']':

		category = CB_CATEGORY_BOOLEAN;
		break;

	case '!':
	case '&':
	case '|':

		if (CB_TREE_CLASS (x) != CB_CLASS_BOOLEAN ||
		    (y && CB_TREE_CLASS (y) != CB_CLASS_BOOLEAN)) {
			cb_error (_("Invalid expression"));
			return cb_error_node;
		}
		category = CB_CATEGORY_BOOLEAN;
		break;

	case '@':

		category = CB_TREE_CATEGORY (x);
		break;

	default:
		fprintf (stderr, "Unexpected operator -> %d\n", op);
		ABORT ();
	}

	p = make_tree (CB_TAG_BINARY_OP, category, sizeof (struct cb_binary_op));
	p->op = op;
	p->x = x;
	p->y = y;
	return CB_TREE (p);
}

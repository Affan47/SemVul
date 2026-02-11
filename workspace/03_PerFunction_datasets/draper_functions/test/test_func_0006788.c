avl_delete(const long b, AvlNode* t)
{
	AvlNode *m;
	int balance_factor;

	if (b == t->cont->id) {

		if (t->height > 1) {
			m = avl_find_max(t->left);
			t->cont = m->cont;

			free(m);
		} else
			free(t);
		return NULL;
	}
	else if (b < t->cont->id) {
		t->left = avl_delete(b, t->left);
		balance_factor = calc_height(t->left) - calc_height(t->right);
		if (balance_factor == 2) {
			if (b < t->left->cont->id)
				t = right_rotation(t);
			else
				t = left_right_rotation(t);
		}
		t->height = max(calc_height(t->left), calc_height(t->right)) + 1;
		return t;
	}
	else if (b > t->cont->id) {
		t->right = avl_delete(b, t->right);
		balance_factor = calc_height(t->right) - calc_height(t->left);
		if (balance_factor == 2) {
			if (b > t->right->cont->id)
				t = left_rotation(t);
			else
				t = right_left_rotation(t);
		}
		t->height = max(calc_height(t->left), calc_height(t->right)) + 1;
		return t;
	}

	return NULL;
}

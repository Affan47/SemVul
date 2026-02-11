stack_push(struct val_node **head, void *val)
{
	struct val_node *node = malloc(sizeof(struct val_node));
	int rc = 0;

	if (!node) {
		rc = -ENOMEM;
		goto out;
	}
	node->val = val;
	node->next = *head;
	*head = node;
out:
	return rc;
}

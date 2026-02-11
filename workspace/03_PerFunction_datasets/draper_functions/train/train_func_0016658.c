evaluate(const nomme &first, const nomme &second) const
    {
	const inode *first_i = get_inode(&first);

	return dynamic_cast<const file *>(first_i) != NULL && dynamic_cast<const door *>(first_i) == NULL;
    }

locationFromIndex(const QModelIndex& idx,
                                          Location& loc) const
{

	if (!idx.isValid())
		return false;

	Node* node = static_cast<Node*>(idx.internalPointer());
	if (node == NULL)
		return false;

	loc = node->data().loc_;
	return true;
}

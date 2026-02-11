deleteStyleNode(Node* node)
{

	for (int i = 0; i < node->childCount(); i++)
		deleteStyleNode(node->child(i));


	StyleData* data = static_cast<StyleData*>(node->data());
	for (int i = 0; i < data->propRoot_.childCount(); i++) {
		Node* child = data->propRoot_.child(i);
		delete child->data();
		data->propRoot_.clear();
	}


	delete data;
}

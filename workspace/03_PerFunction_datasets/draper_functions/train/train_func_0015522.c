create_node(std::string type, int attribute, int classification)
{
	dectree_node* new_node = new dectree_node();
	new_node->type = type;
	std::stringstream ss;


	if(!(type.compare("split")))
	{
		ss << attribute;
		new_node->attribute = ss.str();

		new_node->attribute_id = attribute;
		new_node->output = "none";
		new_node->output_id = -1;

		ss << "";
		ss.clear();


	}


	else
	{

		ss << classification;
		new_node->attribute = "none";
		new_node->attribute_id = -1;
		new_node->output = ss.str();
		new_node->output_id = classification;

		ss << "";
		ss.clear();


	}
	new_node->f = new_node->t = NULL;

	return new_node;
}

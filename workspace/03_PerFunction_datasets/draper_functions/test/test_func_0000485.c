parseVertex(const TiXmlElement *root, struct Vertex *vert)
{
	if(string(root->Value()) != "Vertex")
	{
		fprintf(stderr, "Unknown node type: %s  (required: Vertex)\n", root->Value());
		return -1;
	}

	if(root->QueryFloatAttribute("x", &vert->co[0]) != TIXML_SUCCESS) return -1;
	if(root->QueryFloatAttribute("y", &vert->co[1]) != TIXML_SUCCESS) return -1;
	if(root->QueryFloatAttribute("z", &vert->co[2]) != TIXML_SUCCESS) return -1;

	if(root->QueryFloatAttribute("nx", &vert->no[0]) != TIXML_SUCCESS) return -1;
	if(root->QueryFloatAttribute("ny", &vert->no[1]) != TIXML_SUCCESS) return -1;
	if(root->QueryFloatAttribute("nz", &vert->no[2]) != TIXML_SUCCESS) return -1;

	return 0;
}

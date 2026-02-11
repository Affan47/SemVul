findProperRotationAxes(Symmetry* symmetry)
{
	gint degeneracy = symmetry->degeneracy;
	symmetry->rotations = newElements();
	getPrincipalAxisRotations(symmetry);
	getAtomRotations(symmetry);
	getMidpointRotations(symmetry);
	if(degeneracy == 3) getFaceRotations(symmetry);
	if(degeneracy != 3)
	{
		if(symmetry->primaryAxis == NULL)
		{
			GList* listE = symmetry->elements.getElements(&symmetry->elements);
			GList* l;
			for(l = listE; l != NULL; l = l->next)
			{
				Element* rot = (Element*) l->data;
				if(symmetry->primaryAxis == NULL || rot->getDegree(rot) > symmetry->primaryAxis->getDegree(symmetry->primaryAxis))
				{
					copyElement(rot, &symmetry->primaryAxis);
				}
			}
		}
	}
	else symmetry->primaryAxis = NULL;
}

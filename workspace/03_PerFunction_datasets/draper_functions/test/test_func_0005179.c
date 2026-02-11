ImportElement(vtkScenarioObject *object, vtkXMLDataElement *e){
	vtkScenarioElement *element = vtkScenarioElement::New();
	double *v = new double[3];


	if (e->GetAttribute("Name")) element->SetName(e->GetAttribute("Name"));
	e->GetVectorAttribute("Scale",3,v);
	element->SetScale(v[0],v[1],v[2]);
	e->GetVectorAttribute("Origin",3,v);
	element->SetOrigin(v[0],v[1],v[2]);
	e->GetVectorAttribute("Position",3,v);
	element->SetPosition(v[0],v[1],v[2]);
	e->GetVectorAttribute("Orientation",3,v);
	element->SetOrientation(v[0],v[1],v[2]);
	delete[] v;


	vtkXMLDataElement *models = e->FindNestedElementWithName("Models");
	for (int i=0; i < models->GetNumberOfNestedElements(); i++){
		vtkXMLDataElement *model = models->GetNestedElement(i);
		this->ImportModel(element, model);
	}


	object->AddElement(element);
}

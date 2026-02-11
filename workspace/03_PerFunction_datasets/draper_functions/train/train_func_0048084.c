DisplayInputEdges ()
{
	if (!this->SInput)
	{
		if (!this->Input)
			return;


		int i,j,NPoints=this->Input->GetNumberOfPoints();
		vtkEdgeTable *Table=vtkEdgeTable::New();
		Table->InitEdgeInsertion(NPoints);
		vtkIdList *VList=vtkIdList::New();
		for (i=0;i<this->Input->GetNumberOfCells();i++)
		{
			this->Input->GetCellPoints(i,VList);
			for (j=0;j<VList->GetNumberOfIds();j++)
			{
				if (Table->IsEdge(VList->GetId(j), VList->GetId((j+1)%VList->GetNumberOfIds()))<0)
					Table->InsertEdge(VList->GetId(j), VList->GetId((j+1)%VList->GetNumberOfIds()));
			}
		}

		vtkIdType v1,v2;
		VList->SetNumberOfIds(2);

		vtkPolyData *Edges=vtkPolyData::New();

		Edges->Allocate(Table->GetNumberOfEdges());
		Edges->SetPoints(this->Input->GetPoints());
		Table->InitTraversal();
		for (i=0;i<Table->GetNumberOfEdges();i++)
		{
			Table->GetNextEdge(v1,v2);
			VList->SetId(0,v1);
			VList->SetId(1,v2);
			Edges->InsertNextCell(VTK_LINE,VList);
		}
		this->SetInputEdges (Edges);
		Edges->Delete();
		VList->Delete();
		Table->Delete();
		return;

	}

	vtkPolyData *Edges = this->SInput->GetEdgesPolyData ();
	this->SetInputEdges (Edges);
	Edges->Delete ();
}

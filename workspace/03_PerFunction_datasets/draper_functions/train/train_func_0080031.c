HighLightEdges(vtkIdList *Edges, double Radius)
{
	if(Edges!=0)
	{
		vtkPolyData *EdgesP=vtkPolyData::New();
		vtkIdList *vl=vtkIdList::New();
		vl->SetNumberOfIds(2);

		EdgesP->SetPoints(this->SInput->GetPoints());
		EdgesP->Allocate(Edges->GetNumberOfIds());
		for (int i=0;i<Edges->GetNumberOfIds();i++)
		{
			vtkIdType v1,v2;
			this->SInput->GetEdgeVertices(Edges->GetId(i),v1,v2);
			vl->SetId(0,v1);
			vl->SetId(1,v2);
			EdgesP->InsertNextCell(VTK_LINE,vl);
		}

		EdgesP->Modified();
		vl->Delete();

		vtkTubeFilter *Tube=vtkTubeFilter::New();
		Tube->SetRadius(Radius);
		Tube->SetNumberOfSides(20);
		Tube->SetInput(EdgesP);

		vtkPolyDataMapper* mapper = vtkPolyDataMapper::New( );
		mapper->SetInput( Tube->GetOutput( ) );

		if( !this->HighlightedEdgesActor )
			HighlightedEdgesActor = vtkActor::New( );
		else
			this->GetMeshRenderer()->RemoveActor( HighlightedEdgesActor );

		HighlightedEdgesActor->SetMapper( mapper );
		HighlightedEdgesActor->GetProperty( )->SetColor( 1., 0., 0. );

		this->GetMeshRenderer()->AddActor( HighlightedEdgesActor );
		mapper->Delete( );
		Tube->Delete();
		EdgesP->Delete();
	}
	else
		if( this->HighlightedEdgesActor )
			this->GetMeshRenderer()->RemoveActor( HighlightedEdgesActor );
}

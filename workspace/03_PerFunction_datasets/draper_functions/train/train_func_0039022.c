main( int argc, char *argv[] )
{
	if (argc<2)
	{
		cout<<"Usage : CheckOrientation input"<<endl;
		exit (1);
	}
	vtkSurface *Mesh=vtkSurface::New();
	Mesh->CreateFromFile(argv[1]);

	vtkPolyDataNormals *Normals=vtkPolyDataNormals::New();
	Normals->SetInput(Mesh);
	Normals->SplittingOff();
	Normals->FlipNormalsOn();
	Normals->Update();

	vtkPolyData *Output=Normals->GetOutput();
	Output->GetPointData()->SetScalars(0);
	Output->GetCellData()->SetScalars(0);

	vtkPolyDataWriter *Writer=vtkPolyDataWriter::New();
	Writer->SetInput(Output);
	Writer->SetFileName("good_orientation.vtk");
	Writer->Write();
	Writer->Delete();
	Normals->Delete();
	Mesh->Delete();
	return(0);
}

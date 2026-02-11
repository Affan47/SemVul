main( int argc, char *argv[] )
{
	if (argc<3)
	{
		cout<<"Usage : VolumeMedian file.mhd radius"<<endl;
		exit(1);
	}


	cout <<"load : "<<argv[1]<<endl;

	vtkMetaImageReader *Reader=vtkMetaImageReader::New();
	Reader->SetFileName(argv[1]);
	Reader->Update();
	vtkImageMedian3D *Median=vtkImageMedian3D::New();
	Median->SetInput(Reader->GetOutput());
	int Radius=atoi(argv[2]);
	Median->SetKernelSize(Radius,Radius,Radius);
	Median->Update();
	vtkMetaImageWriter *Writer=vtkMetaImageWriter::New();
	Writer->SetInput(Median->GetOutput());
	Writer->SetFileName("output.mhd");
	Writer->Write();
}

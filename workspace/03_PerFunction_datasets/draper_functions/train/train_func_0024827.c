LoadCamera(const char *filename)
{
	double ClippingRange[2];
	double FocalPoint[3];
	double Position[3];
	double ViewUp[3];
	double ViewAngle;

        vtkCamera *camera=this->GetMeshRenderer()->GetActiveCamera();

	std::ifstream file(filename);

   	if (file)
    	{
        	std::string line;
			std::string res;
      		 while ( std::getline( file, line) )
        	{

			sscanf(line.c_str(),"ClippingRange : %lf %lf",ClippingRange,ClippingRange+1);
			sscanf(line.c_str(),"FocalPoint : %lf %lf %lf",FocalPoint,FocalPoint+1,FocalPoint+2);
			sscanf(line.c_str(),"Position : %lf %lf %lf",Position,Position+1,Position+2);
			sscanf(line.c_str(),"ViewUp : %lf %lf %lf",ViewUp,ViewUp+1,ViewUp+2);
			sscanf(line.c_str(),"ViewAngle : %lf",&ViewAngle);
        	}
    	}
	else
	{
		return(0);
	}

	camera->SetClippingRange(ClippingRange);
	camera->SetFocalPoint(FocalPoint);
	camera->SetPosition(Position);
	camera->SetViewUp(ViewUp);
	camera->SetViewAngle(ViewAngle);
	file.close();

	return(1);
}

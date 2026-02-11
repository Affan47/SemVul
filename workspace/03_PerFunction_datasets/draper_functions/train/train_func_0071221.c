SaveCamera(const char *filename)
{

        vtkCamera *camera=this->GetMeshRenderer()->GetActiveCamera();

	std::ofstream camera_file;
	camera_file.open (filename, ofstream::out | ofstream::trunc);
	double *ClippingRange = camera->GetClippingRange();
	double *FocalPoint = camera->GetFocalPoint();
	double *Position = camera->GetPosition();
	double *ViewUp = camera->GetViewUp();
	double ViewAngle = camera->GetViewAngle();
	camera_file<<"ClippingRange : "<<ClippingRange[0]<<" "<<ClippingRange[1]<<endl;
	camera_file<<"FocalPoint :"<<FocalPoint[0]<<" "<<FocalPoint[1]<<" "<<FocalPoint[2]<<endl;
	camera_file<<"Position : "<<Position[0]<<" "<<Position[1]<<" "<<Position[2]<<endl;
	camera_file<<"ViewUp : "<<ViewUp[0]<<" "<<ViewUp[1]<<" "<<ViewUp[2]<<endl;
	camera_file<<"ViewAngle : "<<ViewAngle<<endl;

	camera_file.close();
}

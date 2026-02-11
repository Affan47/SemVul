getMatrixUsingPosit(vector<CvPoint2D32f> imagePoints, vector<CvPoint3D32f> objectPoints,
		vector<int> selectedPoints,int focus, CvMatr32f rotation_matrix, CvVect32f translation_vector){

	vector<CvPoint3D32f> chosenPoints;
	vector<CvPoint2D32f> chosenImagePoints;

	chosenPoints.push_back(objectPoints[0]);
	chosenImagePoints.push_back(imagePoints[0]);

	for(int i=1;i<selectedPoints.size();i++){
		int index = selectedPoints[i];
		if(index<objectPoints.size()){
			chosenPoints.push_back(objectPoints[index]);
			chosenImagePoints.push_back(imagePoints[index]);

		}

	}

	if(selectedPoints.size()>=4){

		CvPOSITObject *positObject = cvCreatePOSITObject( &chosenPoints[0], static_cast<int>(chosenPoints.size()) );


		CvTermCriteria criteria = cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 1000, 1.0e-5 );
		cvPOSIT( positObject, &chosenImagePoints[0], focus, criteria, rotation_matrix, translation_vector );

		cvReleasePOSITObject (&positObject);
	}
	else{
		printf("Error: no posit: number of points %d\n",chosenPoints.size());
		return 1;

	}

	return 0;

}

loadCascade(CvHaarClassifierCascade** cascade, char* fileName){

	*cascade = (CvHaarClassifierCascade*)cvLoad( fileName, 0, 0, 0 );


	if( !(*cascade) ){
		printf( "ERROR: Could not load classifier cascade. The required file '%s' should be in a 'data' subdirectory under the directory in which the application is being run.\n"
				, fileName);
		exit(1);
	}


}

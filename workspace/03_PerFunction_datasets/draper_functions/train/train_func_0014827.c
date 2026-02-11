example_dilation(){
    CamImage source, decode_dilated_rle, str, source_binary;
    CamRLEImage encoded, dilated, strElmnt;
	CamArithmParams arithm_params;
    int x, y;

	char* ptr;
	CamTable lut;

	char structElt[strElmnt_size][strElmnt_size];

	for(x=0;x<strElmnt_size;x++){
		for(y=0;y<strElmnt_size;y++){
			structElt[x][y] = 1;
		}
	}
	lut.t[0]=0;
	lut.t[1]=255;
	lut.size = 2;

	camLoadPGM(&source,"resources/test_lettres3.pgm");
    camAllocateImage(&source_binary,source.width,source.height,CAM_DEPTH_1U);
    arithm_params.operation=CAM_ARITHM_THRESHOLD;
    arithm_params.c1=55;
    arithm_params.c2=0;
    arithm_params.c3=255;
    camMonadicArithm(&source,&source_binary,&arithm_params);


	camRLEAllocate(&encoded,source.width*source.height);
	camRLEAllocate(&dilated,source.width*source.height);
	camRLEAllocate(&strElmnt, strElmnt_size*strElmnt_size);

	camAllocateImage(&str, strElmnt_size, strElmnt_size, CAM_DEPTH_1U);
	camAllocateImage(&decode_dilated_rle, source.width, source.height, CAM_DEPTH_8U);

	str.nChannels = 1;
	for(x=0; x<strElmnt_size; x++){
		for(y=0; y<strElmnt_size; y++){
			ptr = str.imageData + y*str.widthStep + x;
			*ptr = 255*structElt[x][y];
		}
	}

	camRLEEncode(&source_binary,&encoded);
	camRLEEncode(&source_binary,&dilated);
	camRLEEncode(&str, &strElmnt);


	camRLEDilate(&encoded, &dilated, &strElmnt);


	printf("nbRuns encoded : %d\n", encoded.nbRuns);
	printf("nbRuns dilated : %d\n", dilated.nbRuns);
	printf("nbRuns strElmnt : %d\n", strElmnt.nbRuns);


	camRLEDecode(&dilated, &decode_dilated_rle, &lut);

	camSavePGM(&decode_dilated_rle, "output/dilated.pgm");

	camClone(&source, &decode_dilated_rle);

    camRLEDeallocate(&encoded);
	camRLEDeallocate(&dilated);
	camRLEDeallocate(&strElmnt);
    camDeallocateImage(&source);
	camDeallocateImage(&str);
	camDeallocateImage(&decode_dilated_rle);
	camDeallocateImage(&source_binary);
	printf("Quit!!\n");
}

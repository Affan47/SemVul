example_capture()
{
    void *handle;
    int i;
    CamImage image;

    image.imageData=NULL;

    handle=camCaptureInit(CAM_CAPTURE_AUTO_SOURCE|CAM_CAPTURE_DISPLAY);
    if (handle) {
	for (i=0;i<30;i++) {
	    printf("Grabbing frame #%d...\n",i);
	    camCapture(handle,&image);
	}
	camSaveBMP(&image,"output/capture.bmp");
	camCaptureOver(handle);
	camDeallocateImage(&image);
    } else {
	printf("No camera found\n");
    }
}

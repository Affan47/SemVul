example_me()
{
    CamImage image1,image2;
    CamROI roi1,roi2;
    CamMotionEstimation3DRSParams params;
    CamMotionEstimation3DRSResults results;
    int x,y;

    camLoadPGM(&image1,"resources/chess.pgm");
    camAllocateImage(&image2,image1.width,image1.height,CAM_DEPTH_8U);
    camSet(&image2,0);

    roi1.width=roi2.width=image1.width-10;
    roi1.height=roi2.height=image1.height-8;
    roi1.xOffset=0;
    roi1.yOffset=0;
    roi2.xOffset=10;
    roi2.yOffset=8;

    image1.roi=&roi1;
    image2.roi=&roi2;
    camCopy(&image1,&image2);
    camSavePGM(&image2,"output/chess_translated.pgm");
    camMotionEstimation3DRSInit(&params,0,2,20,16,3,5,0);
    camMotionEstimation3DRS(&image2,&image1,&params,&results);

    for (y=0;y<image2.height/16;y++) {
        for (x=0;x<image2.width/16;x++) {
            printf("(%2d,%2d)",results.vx[x][y],results.vy[x][y]);
        }
        printf("\n");
    }

    camDeallocateImage(&image1);
    camDeallocateImage(&image2);
}

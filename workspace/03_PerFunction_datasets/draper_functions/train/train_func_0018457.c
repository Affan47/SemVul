I_fopen_cam_file_new(char *camera)
{
    FILE *fd;
    char element[100];


    sprintf(element, "camera");

    fd = G_fopen_new(element, camera);
    if (!fd)
	error(camera, "can't create ", "");
    return fd;
}

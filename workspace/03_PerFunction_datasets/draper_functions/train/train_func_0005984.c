filenameChangedCB(void *data, SoSensor *)


{
    SoTexture2 *tex = (SoTexture2 *)data;

    if (tex->filename.isIgnored()) {
	tex->setReadStatus(FALSE);
	return;
    }


    int nx, ny, nc;
    unsigned char *bytes;
    SbBool result = readImage(tex->filename.getValue(), nx, ny, nc, bytes);
    if (!result) {

	nx = ny = nc = 0;
	bytes = NULL;
    }

    tex->imageSensor->detach();


    tex->image.setValue(SbVec2s(nx, ny), nc, bytes);


    tex->image.setDefault(TRUE);

    if (bytes != NULL) delete [] bytes;

    if (tex->renderList) {
	tex->renderList->unref();
	tex->renderList = NULL;
    }
    tex->imageSensor->attach(&tex->image);

    tex->setReadStatus(result);
}

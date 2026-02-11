AnimateGif(ClientData data) {
    GifInfo *Info = (GifInfo *)data;

    if (Info) {
        if (Info->ImageMaster && Info->image) {
            Tk_ImageMaster master = (Tk_ImageMaster) *((void **) Info->Handle);
            if (master == Info->ImageMaster) {

                Info->CurrentFrame++;
                if (Info->CurrentFrame >= Info->NumFrames || Info->image->GetFrame(Info->CurrentFrame) == NULL)
                    Info->CurrentFrame = 0;
                CxImage *image = Info->image->GetFrame(Info->CurrentFrame);
                if (image) {
                    Tk_ImageChanged(Info->ImageMaster, 0, 0, image->GetWidth(), image->GetHeight(), image->GetWidth(), image->GetHeight());
                    Info->timerToken = NULL;
                }
            } else {
                LOG("Image destroyed, deleting... Image Master was : ");
                APPENDLOG( master );
                APPENDLOG(" - ");
                APPENDLOG( Info->ImageMaster);

                Info->image->DestroyFrames();
                delete Info->image;
                LOG("Deleting AnimatedGifInfo");
                APPENDLOG(Info->Handle);
                Tcl_DeleteTimerHandler(Info->timerToken);
                TkCxImage_lstDeleteItem(Info->Handle);
                for (GifBuffersIterator it=Info->buffers.begin(); it!=Info->buffers.end(); it++) {
                    (*it)->Close();
                    delete (*it);
                }
                delete Info;
                Info = NULL;
            }
        } else {
            Tcl_DeleteTimerHandler(Info->timerToken);
            delete Info;
            Info = NULL;
        }
    }
}

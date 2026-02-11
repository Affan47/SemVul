FrameNext(GxView * ) {
    if (frames->isLastFrame())
        return 0;

    frames->Next->Activate();

    return 1;
}

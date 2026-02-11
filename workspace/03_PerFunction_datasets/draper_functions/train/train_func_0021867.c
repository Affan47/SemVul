seekTo(float percent) {


    if(commitlog == 0 || !commitlog->isSeekable()) return;


    if(paused) paused = false;

    reset();

    commitlog->seekTo(percent);
}

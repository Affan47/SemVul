stop()
{
    if (d->movie) {
        d->movie->stop();
        d->movie->jumpToFrame(0);
        d->_k_movieFrameChanged(0);
    } else {
       d->current_frame = 0;
       d->timer.stop();
       d->updateCurrentIcon();
    }
}

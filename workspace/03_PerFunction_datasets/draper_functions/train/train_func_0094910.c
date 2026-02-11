biscTimedSpin(int velocity, int mseconds) {
    if(mseconds <= 0) return BISC_ERR;

    if(biscSpin(velocity)     == BISC_ERR) return BISC_ERR;
    if(biscWaitTime(mseconds) == BISC_ERR) return BISC_ERR;
    if(biscDriveStop()        == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}

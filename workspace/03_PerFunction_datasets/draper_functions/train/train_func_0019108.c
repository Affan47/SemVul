biscSpinAngle(int velocity, int degrees) {
    if(biscSpin(velocity)     == BISC_ERR) return BISC_ERR;
    if(biscWaitAngle(degrees) == BISC_ERR) return BISC_ERR;
    if(biscDriveStop()        == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}

kmclipm_priv_compare_calAngles (const cpl_vector *calAngleFile, const double *calAngleLut ) {
    if (calAngleFile == NULL || cpl_vector_get_size(calAngleFile) !=3) {
        return 0;
    } else if ((fabs(cpl_vector_get(calAngleFile, 0) -calAngleLut[0]) < 0.5) &&
        (fabs(cpl_vector_get(calAngleFile, 1) -calAngleLut[1]) < 0.5) &&
        (fabs(cpl_vector_get(calAngleFile, 2) -calAngleLut[2]) < 0.5) ) {
        return 1;
    } else {
        return 0;
    }
}

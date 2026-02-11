magCalSaveCorr(const char *ellipsoidFitPath)
{
    FILE *file;
    char *corrFile;
    float a[3];
    float b[9];

    if (ellipsoidFitPath != NULL) {
        corrFile = (char *)malloc(strlen(RTIMUCALDEFS_MAG_CORR_FILE) + strlen(ellipsoidFitPath) + 2);
        sprintf(corrFile, "%s/%s", ellipsoidFitPath, RTIMUCALDEFS_MAG_CORR_FILE);
        if ((file = fopen(corrFile, "r")) == NULL) {
            HAL_ERROR("Failed to open ellipsoid fit correction data file\n");
            return false;
        }
        if (fscanf(file, "%f %f %f %f %f %f %f %f %f %f %f %f",
            a + 0, a + 1, a + 2, b + 0, b + 1, b + 2, b + 3, b + 4, b + 5, b + 6, b + 7, b + 8) != 12) {
            HAL_ERROR("Ellipsoid corrcetion file didn't have 12 floats\n");
            fclose(file);
            return false;
        }
        fclose(file);
        m_settings->m_compassCalEllipsoidValid = true;
        m_settings->m_compassCalEllipsoidOffset = RTVector3(a[0], a[1], a[2]);
        memcpy(m_settings->m_compassCalEllipsoidCorr, b, 9 * sizeof(float));
        m_settings->saveSettings();
        return true;
    }
    return false;
}

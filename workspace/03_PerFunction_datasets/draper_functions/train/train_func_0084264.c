isFileModTimeLater(const char *filePath, const char *checkAgainst, UBool isDir) {
    UBool isLatest = TRUE;

    if (filePath == NULL || checkAgainst == NULL) {
        return FALSE;
    }

    if (isDir == TRUE) {
#if U_HAVE_DIRENT_H
        DIR *pDir = NULL;
        if ((pDir= opendir(checkAgainst)) != NULL) {
            DIR *subDirp = NULL;
            DIRENT *dirEntry = NULL;

            while ((dirEntry = readdir(pDir)) != NULL) {
                if (uprv_strcmp(dirEntry->d_name, SKIP1) != 0 && uprv_strcmp(dirEntry->d_name, SKIP2) != 0) {
                    char newpath[MAX_PATH_SIZE] = "";
                    uprv_strcpy(newpath, checkAgainst);
                    uprv_strcat(newpath, U_FILE_SEP_STRING);
                    uprv_strcat(newpath, dirEntry->d_name);

                    if ((subDirp = opendir(newpath)) != NULL) {

                        closedir(subDirp);
                        isLatest = isFileModTimeLater(filePath, newpath, isDir);
                        if (!isLatest) {
                            break;
                        }
                    } else {
                        int32_t latest = whichFileModTimeIsLater(filePath, newpath);
                        if (latest < 0 || latest == 2) {
                            isLatest = FALSE;
                            break;
                        }
                    }

                }
            }
            closedir(pDir);
        } else {
            fprintf(stderr, "Unable to open directory: %s\n", checkAgainst);
            return FALSE;
        }
#endif
    } else {
        if (T_FileStream_file_exists(checkAgainst)) {
            int32_t latest = whichFileModTimeIsLater(filePath, checkAgainst);
            if (latest < 0 || latest == 2) {
                isLatest = FALSE;
            }
        } else {
            isLatest = FALSE;
        }
    }

    return isLatest;
}

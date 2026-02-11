isPreBeta2(char version[4]) {
    return is3_0Alpha(version) || (is3_0Beta(version) && correction(version) == 1);
}

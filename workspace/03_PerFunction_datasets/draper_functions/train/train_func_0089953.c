strTimeFmt(struct tm const & t) {
    return (fmtTimeAlt && (t.tm_sec & 1) ? fmtTimeAlt : fmtTime);
}

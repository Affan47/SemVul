operator+(timeval src1, timeval src2) {
    timeval sum;
    sum.tv_sec = src1.tv_sec + src2.tv_sec;
    sum.tv_usec = src1.tv_usec + src2.tv_usec;
    if (sum.tv_usec >= ONE_SECOND) {
	sum.tv_usec -= ONE_SECOND;
	sum.tv_sec++;
    } else if (sum.tv_sec >= 1 && sum.tv_usec < 0) {
	sum.tv_usec += ONE_SECOND;
	sum.tv_sec--;
    }
    return sum;
}
